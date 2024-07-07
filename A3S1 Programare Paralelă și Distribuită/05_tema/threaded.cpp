#include <algorithm>
#include <condition_variable>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <latch>
#include <mutex>
#include <optional>
#include <queue>
#include <semaphore>
#include <set>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <cassert>
#include <cstdlib>

using namespace std;

/* MessageQueue */

const int MAX_QUEUE_SIZE = 50;

struct ScoreEntry {
  int id;
  int score;
  int country;
};

class MessageQueue {
private:
  queue<ScoreEntry> queue_;
  mutex queue_mutex;

  condition_variable can_send_cond;
  condition_variable can_recv_cond;

  bool closed;
public:
  MessageQueue()
  : queue_(), queue_mutex(),
    can_send_cond(),
    can_recv_cond(),
    closed(false)
  { }

public:
  void close() {
    const lock_guard queue_mutex_guard(this->queue_mutex);
    this->closed = true;
    this->can_recv_cond.notify_all();
  }

  void send(ScoreEntry value) {
    unique_lock queue_mutex_guard(this->queue_mutex);
    this->can_send_cond.wait(
      queue_mutex_guard,
      [this]() {
        return this->queue_.size() < MAX_QUEUE_SIZE;
      }
    );
    this->queue_.push(value);
    this->can_recv_cond.notify_one();
  }

  optional<ScoreEntry> recv() {
    unique_lock queue_mutex_guard(this->queue_mutex);
    this->can_recv_cond.wait(
      queue_mutex_guard,
      [this]() {
        return !this->queue_.empty() || this->closed;
      }
    );

    if (this->queue_.empty()) {
      return {};
    }

    auto result = optional(this->queue_.front());
    this->queue_.pop();
    this->can_send_cond.notify_one();
    return result;
  }
};

/* score stuff */

struct ScoreTotal {
  int id;
  int score;
  int country;

  ScoreTotal(
    int id,
    int score,
    int country
  )
  : id(id), score(score), country(country)
  {}
};

/* linked list */

namespace llist {
  struct Item {
    ScoreTotal score_total;
    mutex mutex_;

    Item(
      ScoreTotal score_total
    )
    : score_total(score_total), mutex_()
    {}
  };

  struct Node {
    Item item;
    Node *next;

    template<typename... Args>
    Node(
      Args &&... args
    )
    : item(forward<Args>(args)...), next(nullptr)
    {}
  };

  struct List {
    Node *head;

    void free() {
      Node *node = head;
      while (node != nullptr) {
        Node *next_node = node->next;
        delete node;
        node = next_node;
      }
    }
  };
}

/* reader_and_maybe_writer */

struct ForWriting {
  string path;
  llist::List &list_;
  mutex &list_mutex;

  ForWriting(
    string path,
    llist::List &list,
    mutex &list_mutex
  ) : path(path), list_(list), list_mutex(list_mutex) 
  { }
};

void reader_and_maybe_writer(
  MessageQueue &queue,
  vector<string> paths,
  latch &finished_reading,
  latch &finished_processing,
  optional<ForWriting> for_writing_maybe
) {
  for (const auto &path : paths) {
    ifstream fin{path};

    // parse out country
    int country;
    {
      string file_name = filesystem::path(path).filename();
      string s = "RezultateC";

      int begin = 0;
      begin += s.size();

      int end = begin;
      while (isdigit(file_name[end])) {
        end++;
      }

      string country_str = file_name.substr(begin, end-begin);
      country = atoi(country_str.c_str());
    }

    // read rows
    {
      int id;
      int score;
      char c;
      while (fin >> id >> c >> score) {
        queue.send({id, score, country});
      }
    }
  }

  finished_reading.arrive_and_wait();

  if (!for_writing_maybe.has_value()) return;
  ForWriting for_writing = for_writing_maybe.value();

  queue.close();
  finished_processing.wait();

  {
    const lock_guard list_mutex_guard(for_writing.list_mutex);

    // put everything into vector
    vector<ScoreTotal> score_totals;
    for (
        llist::Node *node = for_writing.list_.head->next
      ; node != nullptr
      ; node = node->next
    ) {
      score_totals.push_back(node->item.score_total);
    }

    for_writing.list_.free();

    // sort
    sort(
      score_totals.begin(),
      score_totals.end(),
      [](const ScoreTotal &lhs, const ScoreTotal &rhs){
        return 
          lhs.score > rhs.score
          || (
            lhs.score == rhs.score
            && lhs.id < rhs.id
          )
        ;
      }
    );

    // write
    ofstream fout{for_writing.path};
    for (auto const &score_total : score_totals) {
      fout << score_total.id << "," << score_total.score << "," << score_total.country << "\n";
    }
  }
}

/* worker */

void worker(
  MessageQueue &queue,
  mutex &list_mutex,
  llist::List &list,
  mutex &cheaters_mutex,
  set<int> &cheaters,
  latch &finished_processing
) {
  while (true) {
    optional<ScoreEntry> score_entry_maybe = queue.recv();
    if (!score_entry_maybe.has_value()) break;

    ScoreEntry entry = score_entry_maybe.value();

    bool is_cheater = entry.score == -1;

    // NOTE: This mutex must be locked until the moment the thread tries to lock
    // the first item of the list. This is to ensure that all threads go in the
    // same order.
    cheaters_mutex.lock();
    if (cheaters.contains(entry.id)) {
      cheaters_mutex.unlock();
      continue;
    } else if (is_cheater) {
      cheaters.insert(entry.id);
    }

    {
      llist::Node *node_prev = list.head; node_prev->item.mutex_.lock();
      llist::Node *node      = list.head; node = node->next;

      cheaters_mutex.unlock();

      bool found = false;
      while (node != nullptr && !found) {
        node->item.mutex_.lock();

        if (node->item.score_total.id == entry.id) {
          found = true;
          if (is_cheater) {
            node_prev->next = node->next;
          } else {
            node->item.score_total.score += entry.score;
          }
        }

        node_prev->item.mutex_.unlock();
        node_prev = node;
        node = node->next;
      }

      if (!found && !is_cheater) {
        llist::Node *new_node = new llist::Node(ScoreTotal(entry.id, entry.score, entry.country));
        node_prev->next = new_node;
      }
      node_prev->item.mutex_.unlock();
      if (found && is_cheater) {
        delete node_prev;
      }
    }
  }
  finished_processing.count_down();
}

int main(int argc, char **argv) {
  // cli arguments
  string data_dir = argv[1];
  string dest_path = argv[2];
  string time_path = argv[3];
  int p_r = atoi(argv[4]);
  int p_w = atoi(argv[5]);

  // save all paths
  vector<string> file_paths {};
  for (auto const &dir_entry : filesystem::directory_iterator{data_dir}) {
    file_paths.push_back(dir_entry.path());
  }

  // initialize stuff
  MessageQueue queue;

  latch finished_reading {p_r};
  latch finished_processing {p_w};
  
  mutex list_mutex;
  llist::List list;
  list.head = new llist::Node(ScoreTotal(0, 0, 0));
  
  mutex cheaters_mutex;
  set<int> cheaters;

  vector<thread> threads;

  // start reader threads
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  {
    int offset = 0;
    int quotient = file_paths.size() / p_r;
    int remainder = file_paths.size() % p_r;
    for (int i = 0; i < p_r; ++i) {
      int len = quotient;
      if (i < remainder) {
        len += 1;
      }

      optional<ForWriting> for_writing_maybe;
      if (i == 0) {
        for_writing_maybe.emplace(
          dest_path,
          list,
          list_mutex
        );
      }

      vector<string> thread_paths;
      for (int j = 0; j < len; ++j) {
        thread_paths.push_back(file_paths[offset+j]);
      }
    
      threads.emplace_back(
        reader_and_maybe_writer,
        ref(queue),
        thread_paths,
        ref(finished_reading),
        ref(finished_processing),
        for_writing_maybe
      );

      offset += len;
    }
  }

  // start worker threads
  for (int i = 0; i < p_w; ++i) {
    threads.emplace_back(
      worker,
      ref(queue),
      ref(list_mutex),
      ref(list),
      ref(cheaters_mutex),
      ref(cheaters),
      ref(finished_processing)
    );
  }

  // join
  for (auto &thread : threads) {
    thread.join();
  }

  chrono::steady_clock::time_point end = chrono::steady_clock::now();

  double elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
  elapsed /= 1'000'000'000;
  {
    ofstream fout{time_path};
    fout << elapsed << endl;
  }
  
  return 0;
}

#include <filesystem>
#include <fstream>
#include <iostream>
#include <latch>
#include <list>
#include <mutex>
#include <optional>
#include <queue>
#include <semaphore>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include <cstdlib>

using namespace std;

/* MessageQueue */

struct ScoreEntry {
  int id;
  int score;
};

class MessageQueue {
private:
  queue<ScoreEntry> queue_;
  mutex queue_mutex;

  counting_semaphore<> reader_semaphore;

  mutex closed_mutex;
  bool closed;
  latch finished_latch;
  bool finished;
  int readers_no;
public:
  MessageQueue()
  : queue_(), queue_mutex(),
    reader_semaphore(0),
    closed_mutex(), closed(false),
    finished_latch(1), finished(false),
    readers_no(0)
  { }

private:
  void release_all_readers(int readers_no_saved) {
    for (int i = 0; i < readers_no_saved ; ++i) {
      this->reader_semaphore.release();
    }
  }

  void finish() {
    this->finished = true;
    this->finished_latch.count_down();
  }
public:
  void close() {
    this->closed_mutex.lock();
      this->closed = true;
    this->closed_mutex.unlock();
    
    this->queue_mutex.lock();
      bool queue_is_empty = this->queue_.empty();
    this->queue_mutex.unlock();

    bool release_all_readers = false;
    int readers_no_saved;
    if (queue_is_empty) {
      this->closed_mutex.lock();
        this->finish();
        release_all_readers = true;
        readers_no_saved = this->readers_no;
      this->closed_mutex.unlock();
    }

    if (release_all_readers) {
      this->release_all_readers(readers_no_saved);
    }
  }

  void send(ScoreEntry value) {
    this->closed_mutex.lock();
      if (this->closed) {
        this->closed_mutex.unlock();
        return;
      }
    this->closed_mutex.unlock();

    this->queue_mutex.lock();
      this->queue_.push(value);
    this->queue_mutex.unlock();

    this->reader_semaphore.release();
  }

  optional<ScoreEntry> recv() {
    this->closed_mutex.lock();
      if (this->finished) {
        this->closed_mutex.unlock();
        return {};
      }
      this->readers_no += 1;
    this->closed_mutex.unlock();
    
    this->reader_semaphore.acquire();

    this->closed_mutex.lock();
      this->readers_no -= 1;
    this->closed_mutex.unlock();

    optional<ScoreEntry> result;

    this->queue_mutex.lock();
      if (!this->queue_.empty()) {
        result.emplace(this->queue_.front());
        this->queue_.pop();
      }
      bool queue_empty = this->queue_.empty();
    this->queue_mutex.unlock();

    bool release_all_readers = false;
    int readers_no_saved;
    if (queue_empty) {
      this->closed_mutex.lock();
        if (this->closed && !this->finished) {
          this->finish();
          release_all_readers = true;
          readers_no_saved = this->readers_no;
        }
      this->closed_mutex.unlock();
    }

    if (release_all_readers) {
      this->release_all_readers(readers_no_saved);
    }

    return result;
  }

  void wait_finished() {
    this->finished_latch.wait();
  }
};

/* reader_and_maybe_writer */

struct ScoreTotal {
  int id;
  int score;
};

struct ForWriting {
  string path;
  list<ScoreTotal> &list_;
  mutex &list_mutex;

  ForWriting(
    string path,
    list<ScoreTotal> &list,
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
    {
      int id;
      int score;
      char c;
      while (fin >> id >> c >> score) {
        queue.send({id, score});
      }
    }
  }

  finished_reading.arrive_and_wait();

  if (!for_writing_maybe.has_value()) return;
  ForWriting for_writing = for_writing_maybe.value();

  queue.close();
  finished_processing.wait();

  for_writing.list_mutex.lock();
  {
    ofstream fout{for_writing.path};
    for (auto const score_total : for_writing.list_) {
      fout << score_total.id << "," << score_total.score << "\n";
    }
  }
  for_writing.list_mutex.unlock();
}

/* worker */

void worker(
  MessageQueue &queue,
  mutex &list_mutex,
  list<ScoreTotal> &list,
  set<int> &cheaters,
  latch &finished_processing
) {
  while (true) {
    optional<ScoreEntry> score_entry_maybe = queue.recv();
    if (!score_entry_maybe.has_value()) break;

    ScoreEntry score_entry = score_entry_maybe.value();
    int id = score_entry.id;
    int score = score_entry.score;

    list_mutex.lock();
      if (cheaters.find(id) != cheaters.end()) {
        list_mutex.unlock();
        continue;
      }

      ScoreTotal score_total {
        id,
        0,
      };

      // find score total and remove it, if it exists
      for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->id == id) {
          score_total = *it;
          list.erase(it);
          break;
        }
      }

      if (score != -1) {
        // update score and insert it
        score_total.score += score;

        for (auto it = list.begin(); true; ++it) {
          if (
               it == list.end()
            || it->score < score_total.score
            || (it->score == score_total.score && it->id > score_total.id)
          ) {
            list.insert(it, score_total);
            break;
          }
        }
      } else {
        // naughty cheater
        cheaters.insert(id);
      }
    list_mutex.unlock();
  }
  finished_processing.count_down();
}

int main(int argc, char **argv) {
  // cli arguments
  string data_dir = argv[1];
  string dest_path = argv[2];
  string time_path = argv[3];
  int p = atoi(argv[4]);
  int p_r = atoi(argv[5]);
  int p_w = p - p_r;

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
  list<ScoreTotal> list;
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

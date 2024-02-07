int P = 5;
int N = 100;
int T = 5; // ms
int MAX = 30;
int C = 15;
// int Administrator = 1;
int TA = 15; // ms

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <map>
#include <deque>
#include <semaphore>
#include <random>
#include <fstream>

struct Carte {
  std::string nume;
  std::string autor;
};

std::string random_string() {
  std::random_device rd;
  std::mt19937 rng(rd());

  std::string str = "";
  for (int i = 0; i < 5; ++i) {
    str += 'a' + std::uniform_int_distribution<>(0, 'z'-'a')(rng);
  }

  return str;
}

void departament_worker(
  std::deque<Carte> &queue,
  std::mutex &queue_mut,
  std::condition_variable &queue_cond,
  std::counting_semaphore<> &queue_sem,

  int &messages_no,
  std::mutex &messages_no_mut
) {
  while (true) {
    int messages_to_produce_no;
    {
      std::lock_guard lk(messages_no_mut);

      if (messages_no == 0) {
        return;
      }

      messages_to_produce_no = std::min(10, messages_no);
      messages_no -= messages_to_produce_no;
    }

    for (int i = 0; i < messages_to_produce_no; ++i) {
      Carte carte {
        random_string(),
        random_string(),
      };
      
      queue_sem.acquire();
      {
        std::lock_guard lk(queue_mut);
        queue.push_back(carte);
      }
      queue_cond.notify_one();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(T));
  }
}

void bibliotecar_worker(
  bool &departamente_gata,

  std::deque<Carte> &queue,
  std::mutex &queue_mut,
  std::condition_variable &queue_cond,
  std::counting_semaphore<> &queue_sem,

  std::map<char, std::vector<Carte>> &map_nume,
  std::mutex &map_nume_mut,

  std::map<char, std::vector<Carte>> &map_autor,
  std::mutex &map_autor_mut
) {
  while (true) {
    Carte carte;
    {
      std::unique_lock lk(queue_mut);
      queue_cond.wait(lk, [&queue, &departamente_gata](){ return !queue.empty() || departamente_gata; });
      if (departamente_gata) {
        return;
      }
      carte = queue.front();
      queue.pop_front();
      queue_sem.release();
    }

    // std::cout << carte.nume << " " << carte.autor << "\n";

    {
      std::lock_guard lk(map_nume_mut);
      char key = carte.nume[0];
      if (!map_nume.contains(key)) {
        map_nume[key] = {};
      }

      std::vector<Carte> &carti = map_nume[key];
      for (auto it = carti.begin(); it <= carti.end(); ++it) {
        if (it == carti.end() || carte.nume < it->nume) {
          carti.insert(it, carte);
          break;
        }
      }
    }

    {
      std::lock_guard lk(map_autor_mut);
      char key = carte.autor[0];
      if (!map_autor.contains(key)) {
        map_autor[key] = {};
      }

      std::vector<Carte> &carti = map_autor[key];
      for (auto it = carti.begin(); it <= carti.end(); ++it) {
        if (it == carti.end() || carte.autor < it->autor) {
          carti.insert(it, carte);
          break;
        }
      }
    }
  }
}

void administrator_worker(
  bool &bibliotecari_gata,
  std::mutex &bibliotecari_gata_mut,

  int &messages_no,
  std::mutex &messages_no_mut,

  std::map<char, std::vector<Carte>> &map_nume,
  std::mutex &map_nume_mut,

  std::map<char, std::vector<Carte>> &map_autor,
  std::mutex &map_autor_mut
) {
  std::ofstream fout("output.txt");
  while (true) {
    {
      std::lock_guard lk1(messages_no_mut);
      std::lock_guard lk2(map_nume_mut);
      std::lock_guard lk3(map_autor_mut);

      int correct_count = N - messages_no;

      int map_nume_count = 0;
      for (const auto &entry : map_nume) {
        map_nume_count += entry.second.size();
      }

      int map_autor_count = 0;
      for (const auto &entry : map_autor) {
        map_autor_count += entry.second.size();
      }

      fout << "NUME: " << (map_nume_count == correct_count) << ": " << map_nume_count << " " << correct_count << "\n";
      fout << "AUTOR: " << (map_autor_count == correct_count) << ": " << map_autor_count << " " << correct_count << "\n";
      fout.flush();

      {
        std::lock_guard lk(bibliotecari_gata_mut);
        if (bibliotecari_gata) {
          return;
        }
      }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(TA));
  }
}

int main() {
  // variabile
  int messages_no = N;
  std::mutex messages_no_mut;

  std::deque<Carte> queue;
  std::mutex queue_mut;
  std::condition_variable queue_cond;
  std::counting_semaphore<> queue_sem(MAX);

  std::map<char, std::vector<Carte>> map_nume;
  std::mutex map_nume_mut;

  std::map<char, std::vector<Carte>> map_autor;
  std::mutex map_autor_mut;

  bool departamente_gata = false;

  bool bibliotecari_gata = false;
  std::mutex bibliotecari_gata_mut;

  // program
  std::vector<std::thread> departamente;
  for (int i = 0; i < P; ++i) {
    departamente.emplace_back(
      departament_worker,

      std::ref(queue),
      std::ref(queue_mut),
      std::ref(queue_cond),
      std::ref(queue_sem),

      std::ref(messages_no),
      std::ref(messages_no_mut)
    );
  }

  std::vector<std::thread> bibliotecari;
  for (int i = 0; i < C; ++i) {
    bibliotecari.emplace_back(
      bibliotecar_worker,

      std::ref(departamente_gata),

      std::ref(queue),
      std::ref(queue_mut),
      std::ref(queue_cond),
      std::ref(queue_sem),

      std::ref(map_nume),
      std::ref(map_nume_mut),

      std::ref(map_autor),
      std::ref(map_autor_mut)
    );
  }

  std::thread administrator(
    administrator_worker,

    std::ref(bibliotecari_gata),
    std::ref(bibliotecari_gata_mut),

    std::ref(messages_no),
    std::ref(messages_no_mut),

    std::ref(map_nume),
    std::ref(map_nume_mut),

    std::ref(map_autor),
    std::ref(map_autor_mut)
  );

  // join
  for (auto &t : departamente) {
    t.join();
  }

  {
    std::lock_guard lk(queue_mut);
    departamente_gata = true;
    queue_cond.notify_all();
  }
  
  for (auto &t : bibliotecari) {
    t.join();
  }

  {
    std::lock_guard lk(bibliotecari_gata_mut);
    bibliotecari_gata = true;
  }

  administrator.join();
  
  return 0;
}

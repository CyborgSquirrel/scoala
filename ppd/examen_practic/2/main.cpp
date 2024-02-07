#include <mutex>
int S = 3;      // thread-uri
int Ys = 100;   // cereri de aterizare
int Tsmin = 10; // ms
int Tsmax = 30; // ms
int P = 3;      // thread-uri
int Yp = 100;   // cereri de decolare
int Tpmin = 10; // ms
int Tpmax = 30; // ms
int T = 8;      // NOTE: unused because useless
int TQp = 4;
int TQs = 4;
int Ls = 3;     // aterizări
int Lp = 3;     // decolări
int Rt = 50;    // ms
int Xmin = 5;   // ms
int Xmax = 10;  // ms
int PC = 1;     // thread

#include <fstream>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <deque>
#include <string>
#include <random>
#include <semaphore>
#include <vector>

struct Cerere {
  long long timestamp;
  int id_avion;
  std::string tip; // "sosire"/"plecare"
  std::string locatie; // "de unde"/"destinatia"
};

// tii cont undeva cate request-uri se proceseaza
// astepti cu cond ca sa fie gata

void generator_worker(
  std::string tip, // "sosire"/"plecare"
  int delay_min,
  int delay_max,

  std::deque<Cerere> &queue,
  std::mutex &mut,
  std::condition_variable &cond
) {
  std::random_device rd;
  std::mt19937 rng(rd());

  while (true) {
    {
      std::lock_guard lk(mut);

      auto duration = std::chrono::system_clock::now().time_since_epoch();
      auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

      Cerere cerere {
        timestamp,
        std::uniform_int_distribution<>(0, 100)(rng),
        tip,
        "locatie",
      };
      queue.push_back(cerere);
      cond.notify_one();
    }
    
    int delay = std::uniform_int_distribution<>(delay_min, delay_max)(rng);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
}

void coada_worker(
  std::deque<Cerere> &queue,
  std::mutex &mut,
  std::condition_variable &cond,

  std::counting_semaphore<> &sem,

  std::vector<Cerere> &cereri_acceptate,
  std::mutex &cereri_acceptate_mut
) {
  std::random_device rd;
  std::mt19937 rng(rd());

  while (true) {
    Cerere cerere;
    {
      std::unique_lock lk(mut);
      cond.wait(lk, [&queue](){ return queue.size() > 0; });
      cerere = queue.front();
      queue.pop_front();
    }
    
    sem.acquire();

    int X = std::uniform_int_distribution<>(Xmin, Xmax)(rng);
    std::this_thread::sleep_for(std::chrono::milliseconds(X));
    
    sem.release();

    {
      std::lock_guard lk(cereri_acceptate_mut);
      cereri_acceptate.push_back(cerere);
    }
  }
}

void panou_worker(
  std::deque<Cerere> &decolare_queue,
  std::mutex &decolare_mut,

  std::deque<Cerere> &aterizare_queue,
  std::mutex &aterizare_mut,

  std::vector<Cerere> &cereri_acceptate,
  std::mutex &cereri_acceptate_mut
) {
  while (true) {
    {
      std::ofstream fout("output.txt");

      fout << "=== CERERI IN ASTEPTARE ===\n";

      {
        std::lock_guard lk(decolare_mut);
        for (const auto &cerere : decolare_queue) {
          fout
            << cerere.timestamp << " "
            << cerere.id_avion << " "
            << cerere.tip << " "
            << cerere.locatie << "\n";
        }
      }

      {
        std::lock_guard lk(aterizare_mut);
        for (const auto &cerere : aterizare_queue) {
          fout
            << cerere.timestamp << " "
            << cerere.id_avion << " "
            << cerere.tip << " "
            << cerere.locatie << "\n";
        }
      }

      fout << "=== CERERI EFECTUATE ===\n";

      {
        std::lock_guard lk(cereri_acceptate_mut);
        for (const auto &cerere : cereri_acceptate) {
          fout
            << cerere.timestamp << " "
            << cerere.id_avion << " "
            << cerere.tip << " "
            << cerere.locatie << "\n";
        }
      }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(Rt));
  }
}

int main() {
  // decolare
  std::deque<Cerere> decolare_queue;
  std::mutex decolare_mut;
  std::condition_variable decolare_cond;
  std::counting_semaphore<> decolare_sem(Lp);

  // aterizare
  std::deque<Cerere> aterizare_queue;
  std::mutex aterizare_mut;
  std::condition_variable aterizare_cond;
  std::counting_semaphore<> aterizare_sem(Ls);

  // cereri_acceptate
  std::vector<Cerere> cereri_acceptate;
  std::mutex cereri_acceptate_mut;

  // program
  std::vector<std::thread> threaduri;

  // sosire
  for (int i = 0; i < S; ++i) {
    threaduri.emplace_back(
      generator_worker,
      "sosire",
      Tsmin,
      Tsmax,
      std::ref(aterizare_queue),
      std::ref(aterizare_mut),
      std::ref(aterizare_cond)
    );
  }

  // plecare
  for (int i = 0; i < P; ++i) {
    threaduri.emplace_back(
      generator_worker,
      "plecare",
      Tpmin,
      Tpmax,
      std::ref(decolare_queue),
      std::ref(decolare_mut),
      std::ref(decolare_cond)
    );
  }

  for (int i = 0; i < TQs; ++i) {
    threaduri.emplace_back(
      coada_worker,
      std::ref(aterizare_queue),
      std::ref(aterizare_mut),
      std::ref(aterizare_cond),
      std::ref(aterizare_sem),
      std::ref(cereri_acceptate),
      std::ref(cereri_acceptate_mut)
    );
  }

  for (int i = 0; i < TQp; ++i) {
    threaduri.emplace_back(
      coada_worker,
      std::ref(decolare_queue),
      std::ref(decolare_mut),
      std::ref(decolare_cond),
      std::ref(decolare_sem),
      std::ref(cereri_acceptate),
      std::ref(cereri_acceptate_mut)
    );
  }

  threaduri.emplace_back(
    panou_worker,
    std::ref(decolare_queue),
    std::ref(decolare_mut),
    std::ref(aterizare_queue),
    std::ref(aterizare_mut),
    std::ref(cereri_acceptate),
    std::ref(cereri_acceptate_mut)
  );

  for (auto &thread : threaduri) {
    thread.join();
  }
  
  return 0;
}

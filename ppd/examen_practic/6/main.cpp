int Yc = 50;     // comenzi
int Tcmin = 170; // ms
int Tcmax = 200; // ms
int B = 2;       // thread-uri
int C = 3;       // thread-uri
int Xbmin = 100; // ms
int Xbmax = 200; // ms
int Rn = 200;    // ms
int N = 1;       // thread
int Dt = 7000;   // ms
  
#include <cassert>
#include <random>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <string>
#include <deque>
#include <map>

struct Comanda {
  int id_comanda;
  std::string tip_mancare;
};

std::deque<Comanda> comenzi;
std::mutex comenzi_mut;
std::condition_variable comenzi_cond;

int last_id_comanda = 0;
std::mutex last_id_comanda_mut;

std::map<int, std::string> registru;
std::mutex registru_mut;

std::string tipuri_mancare[3] = { "sushi", "pizza", "paste" };

std::deque<Comanda> cozi_echipa[3];
std::mutex cozi_echipa_mut[3];
std::condition_variable cozi_echipa_cond[3];

std::vector<Comanda> comenzi_finalizate;
std::mutex comenzi_finalizate_mut;

bool sa_terminat = false;
std::mutex sa_terminat_mut;

void generator_worker() {
  std::random_device rd;
  std::mt19937 rng(rd());
  for (int i = 0; i < Yc; ++i) {
    {
      std::lock_guard lk(sa_terminat_mut);
      if (sa_terminat) {
        return;
      }
    }
    
    {
      int tip_mancare_index = std::uniform_int_distribution<>(0, 2)(rng);
      std::string tip_mancare = tipuri_mancare[tip_mancare_index];

      int id_comanda;
      {
        std::lock_guard lk(last_id_comanda_mut);
        id_comanda = last_id_comanda;
        last_id_comanda += 1;
      }
      
      Comanda comanda { id_comanda, tip_mancare };
      std::unique_lock lk(comenzi_mut);
      comenzi.push_back(comanda);
      comenzi_cond.notify_one();
    }

    {
      int Tc = std::uniform_int_distribution<>(Tcmin, Tcmax)(rng);
      std::this_thread::sleep_for(std::chrono::milliseconds(Tc));
    }
  }
}

void receptioner_worker() {
  while (true) {
    Comanda comanda;
    {
      std::unique_lock lk(comenzi_mut);
      comenzi_cond.wait(lk, [](){ return !comenzi.empty() || sa_terminat; });
      if (comenzi.empty()) {
        return;
      }
      comanda = comenzi.front();
      comenzi.pop_front();
    }

    int tip_mancare_index = -1;
    for (int i = 0; i < 3; ++i) {
      if (comanda.tip_mancare == tipuri_mancare[i]) {
        tip_mancare_index = i;
        break;
      }
    }
    assert(tip_mancare_index != -1);

    {
      std::lock_guard lk(registru_mut);
      registru[comanda.id_comanda] = "in asteptare";
    }
    
    {
      std::lock_guard lk(cozi_echipa_mut[tip_mancare_index]);
      cozi_echipa[tip_mancare_index].push_back(comanda);
      cozi_echipa_cond[tip_mancare_index].notify_one();
    }
  }
}

void echipa_worker(int tip_mancare_index) {
  std::random_device rd;
  std::mt19937 rng(rd());

  std::deque<Comanda> &coada_echipa = cozi_echipa[tip_mancare_index];
  std::mutex &coada_echipa_mut = cozi_echipa_mut[tip_mancare_index];
  std::condition_variable &coada_echipa_cond = cozi_echipa_cond[tip_mancare_index];
  
  while (true) {
    Comanda comanda;
    {
      std::unique_lock lk(coada_echipa_mut);
      coada_echipa_cond.wait(lk, [&coada_echipa](){ return !coada_echipa.empty() || sa_terminat; });
      if (coada_echipa.empty()) {
        return;
      }
      comanda = coada_echipa.front();
      coada_echipa.pop_front();
    }

    {
      std::lock_guard lk(registru_mut);
      registru[comanda.id_comanda] = "in procesare";
    }

    {
      int Xb = std::uniform_int_distribution<>(Xbmin, Xbmax)(rng);
      std::this_thread::sleep_for(std::chrono::milliseconds(Xb));
    }

    {
      std::lock_guard lk(registru_mut);
      registru[comanda.id_comanda] = "finalizata";
    }

    {
      std::lock_guard lk(comenzi_finalizate_mut);
      // std::cout << "comenzi_finalizate: " << comanda.id_comanda << ": " << comanda.tip_mancare << "\n";
      comenzi_finalizate.push_back(comanda);
    }
  }
}

void notificare_worker() {
  std::ofstream fout("output.txt");
  
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

  while (true) {
    {
      auto duration = std::chrono::system_clock::now().time_since_epoch();
      auto now = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

      if (now-begin >= Dt) {
        sa_terminat_mut.lock();

        comenzi_mut.lock();
        comenzi_cond.notify_all();

        for (int i = 0; i < 3; ++i) {
          cozi_echipa_mut[i].lock();
          cozi_echipa_cond[i].notify_all();
        }
      
        sa_terminat = true;

        sa_terminat_mut.unlock();
        comenzi_mut.unlock();
        for (int i = 0; i < 3; ++i) {
          cozi_echipa_mut[i].unlock();
        }

        return;
      }
    }

    std::map<std::string, int> totale;
    totale["in asteptare"] = 0;
    totale["in procesare"] = 0;
    totale["finalizata"] = 0;

    {
      std::lock_guard lk(registru_mut);
      for (const auto &entry : registru) {
        totale[entry.second] += 1;
      }
    }

    std::cout << "=== TOTALE ===\n";
    for (const auto &entry : totale) {
      std::cout << entry.first << ": " << entry.second << "\n";
      fout << entry.first << ": " << entry.second << "\n";
    }
    std::cout << "\n";

    fout.flush();

    auto duration = std::chrono::system_clock::now().time_since_epoch();
    auto now = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

    std::cout << "=== COMENZI FINALIZATE ===\n";
    std::cout << "TIMESTAMP: " << now << "\n";
    {
      std::lock_guard lk(comenzi_finalizate_mut);
      for (const auto &comanda : comenzi_finalizate) {
        std::cout << comanda.id_comanda << ": " << comanda.tip_mancare << "\n";
      }
    }
    std::cout << "\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(Rn));
  }
}

int main() {
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  std::random_device rd;
  std::mt19937 rng(rd());

  // pornim thread-uri
  std::vector<std::thread> generatori;
  for (int i = 0; i < C; ++i) {
    generatori.emplace_back(generator_worker);
  }

  std::vector<std::thread> receptioneri;
  for (int i = 0; i < B; ++i) {
    receptioneri.emplace_back(receptioner_worker);
  }

  std::vector<std::thread> echipe;
  for (int i = 0; i < 3; ++i) {
    echipe.emplace_back(echipa_worker, i);
  }

  std::thread notificare(notificare_worker);

  // join thread-uri
  for (auto &t : generatori) {
    t.join();
  }

  for (auto &t : receptioneri) {
    t.join();
  }

  for (auto &t : echipe) {
    t.join();
  }

  notificare.join();

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  elapsed /= 1'000'000'000;

  std::cout << "=== DURATA EXECUTIE PROGRAM ===\n";
  std::cout << elapsed << "\n";

  return 0;
}

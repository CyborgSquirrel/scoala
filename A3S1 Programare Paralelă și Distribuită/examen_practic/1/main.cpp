#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <cstdint>
#include <random>
#include <vector>
#include <condition_variable>
#include <fstream>

int C = 10;  // animale
int I = 3;   // îngrijitori
int X = 10;  // ms
int Y = 30;  // ms
int Ct = 7;  // ms
int N = 5;   // porții
int T = 6;   // ms
int Pt = 20; // ms
int At = 12; // ms
int H = 0;   // porții

struct RegistruLinie {
  int id;
  int nr_portii;
  std::int64_t timp;
  std::string status;
};

class Curte {
  int count_;
  bool inchisa;
  std::mutex mut;
  std::condition_variable cond;
public:
  Curte() : count_(H), inchisa(false), mut(), cond() { }

  void inchide() {
    std::lock_guard<std::mutex> g {mut};
    inchisa = true;
    cond.notify_all();
  }

  int count() {
    std::lock_guard<std::mutex> g {mut};
    return count_;
  }
  
  bool ofera(int count) {
    std::lock_guard<std::mutex> g {mut};
    if (count_ <= 0) {
      count_ += count;
      cond.notify_one();
      return true;
    } else {
      return false;
    }
  }

  bool consuma() {
    std::unique_lock<std::mutex> g {mut};
    cond.wait(g, [this]() { return this->count_ > 0 || this->inchisa; });
    // std::cout << "curte inchisa? " << inchisa << "\n";
    if (!inchisa) {
      count_--;
    }
    return !inchisa;
  }
};

struct Buletin {
  int id;
  std::string nume;
};

void ingrijitor_worker(
  Buletin buletin,
  Curte &curte,
  std::vector<RegistruLinie> &registru,
  std::mutex &registru_mut
) {
  // std::cout << "ingrijitor: " << buletin.id << " " << buletin.nume << "\n";

  std::random_device rd;
  std::mt19937 rng(rd());
  int It = std::uniform_int_distribution<>(X, Y)(rng);

  int mancare = 100;
  while (mancare > 0) {
    std::this_thread::sleep_for(std::chrono::milliseconds(It));

    int nr_portii = std::min(std::uniform_int_distribution<>(1, N)(rng), mancare);
    if (curte.ofera(nr_portii)) {
  //     std::cout << "ingrijitor: " << buletin.id << " " << mancare << "\n";
      mancare -= nr_portii;
      {
        std::lock_guard<std::mutex> g {registru_mut};
        auto duration = std::chrono::system_clock::now().time_since_epoch();
        auto timp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        registru.push_back({buletin.id, nr_portii, timp, "oferit"});
      }
    }
  }
}

void animal_worker(
  Buletin buletin,
  Curte &curte,
  std::vector<RegistruLinie> &registru,
  std::mutex &registru_mut
) {
  // std::cout << "animal: " << buletin.id << " " << buletin.nume << "\n";
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(Ct));

    if (!curte.consuma()) {
      return;
    }

  //   std::cout << "animal: " << buletin.id << "\n";

    {
      std::lock_guard<std::mutex> g {registru_mut};
      auto duration = std::chrono::system_clock::now().time_since_epoch();
      auto timp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
      registru.push_back({buletin.id, 1, timp, "consumat"});
    }
  }
}

void administrator_worker(
  Curte &curte,
  std::vector<RegistruLinie> &registru,
  std::mutex &registru_mut,
  bool &gata_animale,
  std::mutex &gata_animale_mut
) {
  std::ofstream fout("output.txt");
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(At));
    {
      std::lock_guard<std::mutex> g {registru_mut};
      int portii_oferite = 0;
      int portii_consumate = 0;

      for (const auto &linie : registru) {
        if (linie.status == "oferit") {
          portii_oferite += linie.nr_portii;
        }
        if (linie.status == "consumat") {
          portii_consumate += linie.nr_portii;
        }
        
        fout
          << linie.id << " "
          << linie.nr_portii << " "
          << linie.timp << " "
          << linie.status << "\n";
      }
      fout << "VERIFICAT: " << portii_oferite << " " << portii_consumate << "\n";
      fout.flush();

      // ultima iterare
      {
        std::lock_guard<std::mutex> g {gata_animale_mut};
        if (gata_animale) {
          std::cout << "BILANTUL SE VERIFICA??? " << (portii_oferite == curte.count() + portii_consumate) << "\n";
          return;
        }
      }
    }
  }
}

std::string nume_random() {
  std::random_device rd;
  std::mt19937 rng(rd());

  std::string nume = "";
  for (int i = 0; i < 5; ++i) {
    nume += 'a' + std::uniform_int_distribution<>(0, 'z'-'a')(rng);
  }
  return nume;
}

int main() {
  // variabile
  Curte curte;

  std::vector<RegistruLinie> registru;
  std::mutex registru_mut;

  bool gata_animale;
  std::mutex gata_animale_mut;

  // program
  std::vector<std::thread> ingrijitori;
  for (int i = 0; i < I; ++i) {
    Buletin b { i, nume_random() };
    ingrijitori.emplace_back(
      ingrijitor_worker,
      b,
      std::ref(curte),
      std::ref(registru),
      std::ref(registru_mut)
    );
  }

  std::vector<std::thread> animale;
  for (int i = 0; i < C; ++i) {
    Buletin b { i, nume_random() };
    animale.emplace_back(
      animal_worker,
      b,
      std::ref(curte),
      std::ref(registru),
      std::ref(registru_mut)
    );
  }

  std::thread administrator(
    administrator_worker,
      std::ref(curte),
      std::ref(registru),
      std::ref(registru_mut),
      std::ref(gata_animale),
      std::ref(gata_animale_mut)
  );

  for (auto &t : ingrijitori) {
    t.join();
  }
  curte.inchide(); // s-a inchis curtea
  // std::cout << "gata ingrijitori\n";

  for (auto &t : animale) {
    t.join();
  }
  // std::cout << "gata animale\n";

  {
    std::lock_guard<std::mutex> g {gata_animale_mut};
    gata_animale = true;
  }

  administrator.join();
  
  return 0;
}

int n = 5;
int c_no = 100;

#include <random>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class Cursant {
public:
  int id;
  float medie;
  Cursant(int id, float medie) : id(id), medie(medie) { }
};

struct Nod {
  Cursant cursant;
  Nod *next;

  Nod(Cursant cursant, Nod *next) : cursant(cursant), next(next) { }
};

Nod *catalog;
std::mutex catalog_mut;

std::condition_variable sub_5_cond;
std::mutex sub_5_mut;
bool sub_5 = false;

bool gata_secretare = false;

void secretara_worker(
  std::vector<Cursant> cursanti
) {
  Nod **p = &catalog;
  for (const auto cursant : cursanti) {
    {
      std::lock_guard lk(catalog_mut);
      while (*p != nullptr) {
        p = &((*p)->next);
      }
      *p = new Nod(cursant, nullptr);
    }

    if (cursant.medie < 5) {
      std::lock_guard lk(sub_5_mut);
      sub_5 = true;
      sub_5_cond.notify_one();
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}

void manager_worker() {
  while (true) {
    {
      std::unique_lock lk(sub_5_mut);
      sub_5_cond.wait(lk, [](){ return sub_5 || gata_secretare; });
      if (!sub_5) {
        std::cout << "BEHOLD THE CATALOG\n";
        Nod *p = catalog;
        while (p != nullptr) {
          std::cout << p->cursant.id << " " << p->cursant.medie << "\n";
          p = p->next;
        }
        
        return;
      }
      sub_5 = false;
    }

    std::cout << "luptatori pentru 5:\n";
    {
      std::lock_guard lk(catalog_mut);
      Nod *p = catalog;
      while (p != nullptr) {
        if (p->cursant.medie < 5) {
          std::cout << p->cursant.id << " " << p->cursant.medie << "\n";
        }
        
        p = p->next;
      }
    }
    std::cout << "\n";
  }
}

int main() {
  std::random_device rd;
  std::mt19937 rng(rd());

  std::vector<Cursant> cursanti;
  for (int i = 0; i < c_no; ++i) {
    float medie = std::uniform_real_distribution<>(0, 10)(rng);
    cursanti.push_back(Cursant(i, medie));
  }

  std::vector<std::thread> secretare;
  {
    int p = 0;
    for (int i = 0; i < n; ++i) {
      int len = c_no / n;
      if (i < c_no % n) len++;

      std::vector<Cursant> cursanti_slice = std::vector<Cursant>(cursanti.begin()+p, cursanti.begin()+p+len);
      secretare.emplace_back(
        secretara_worker,
        cursanti_slice
      );
      
      p += len;
    }
  }

  std::thread manager(manager_worker);

  for (auto &t : secretare) {
    t.join();
  }
  {
    std::lock_guard lk(sub_5_mut);
    gata_secretare = true;
    sub_5_cond.notify_all();
  }

  manager.join();
  
  // std::vector<std::thread> secretare;
  
  return 0;
}

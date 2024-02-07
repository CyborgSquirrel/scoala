int t_c = 25;
int t_r = 15;
int t_t = 30;
int t_d = 30;
int R = 5;
int W = 3;

#include <iostream>
#include <fstream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <map>
#include <set>
#include <random>
#include <vector>
#include <string>

struct Tichet {
  int id;
  int serviciu;
};

struct Status {
  int serviciu;
  std::set<int> istoric;
};

int timpi[4] = { t_c, t_r, t_d, t_t };

std::deque<Tichet> tichete;
std::mutex tichete_mut;
std::condition_variable tichete_cond;

std::deque<Tichet> tichete_locale[4];
std::mutex tichete_locale_mut[4];
std::condition_variable tichete_locale_cond[4];

std::map<int, Status> status;
std::mutex status_mut;

bool cititori_gata = false;

bool preluatori_gata = false;

void cititor_worker(
  std::string fisier
) {
  std::ifstream fin(fisier);
  Tichet tichet;
  while (fin >> tichet.id >> tichet.serviciu) {
    {
      std::lock_guard lk(tichete_mut);
      tichete.push_back(tichet);
      tichete_cond.notify_one();
    }
  }
}

void preluator_worker() {
  while (true) {
    Tichet tichet;
    {
      std::unique_lock lk(tichete_mut);
      tichete_cond.wait(lk, [](){ return !tichete.empty() || cititori_gata; });
      if (tichete.empty()) {
        return;
      }
      tichet = tichete.front();
      tichete.pop_front();
    }

    {
      int index = tichet.serviciu - 1;
      std::lock_guard lk(tichete_locale_mut[index]);
      tichete_locale[index].push_back(tichet);
    }
  }
}

void serviciu_worker(
  std::deque<Tichet> &tichete,
  std::mutex &tichete_mut,
  std::condition_variable &tichete_cond,
  int timp
) {
  std::random_device rd;
  std::mt19937 rng(rd());

  while (true) {
    Tichet tichet;
    {
      std::unique_lock lk(tichete_mut);
      tichete_cond.wait(lk, [&tichete](){ return !tichete.empty() || preluatori_gata; });
      if (tichete.empty()) {
        return;
      }
      tichet = tichete.front();
      tichete.pop_front();
    }

    std::cout << tichet.serviciu << " " << tichet.id << "\n";

    {
      std::lock_guard lk(status_mut);
      if (!status.contains(tichet.id)) {
        status[tichet.id] = { 0, {} };
      }

      if (status[tichet.id].serviciu != 0) {
        std::cout << "oopsie, e ocupat deja!\n";
        {
          std::unique_lock lk(tichete_mut);
          tichete.push_front(tichet);
        }
        tichete_cond.notify_one();
        continue;
      }

      status[tichet.id].serviciu = tichet.serviciu;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(timp));

    {
      std::lock_guard lk(status_mut);
      status[tichet.id].serviciu = 0;
      status[tichet.id].istoric.insert(tichet.serviciu);

      if (tichet.serviciu == 1) {
        int roll = std::uniform_int_distribution<>(0, 10)(rng);
        if (roll == 0) {
          std::lock_guard lk(tichete_mut);
          tichete.push_back({ tichet.id, 2 });
          tichete_cond.notify_one();
        }
      }
    }
  }
}

int main() {
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  // trezirea
  std::vector<std::thread> cititori;
  for (int i = 0; i < R; ++i) {
    cititori.emplace_back(
      cititor_worker,
      std::to_string(i)
    );
  }

  std::vector<std::thread> preluatori;
  for (int i = 0; i < W; ++i) {
    preluatori.emplace_back(
      preluator_worker
    );
  }

  std::vector<std::thread> serviciitori;
  for (int i = 0; i < 4; ++i) {
    serviciitori.emplace_back(
      serviciu_worker,
      std::ref(tichete_locale[i]),
      std::ref(tichete_locale_mut[i]),
      std::ref(tichete_locale_cond[i]),
      timpi[i]
    );
  }

  for (auto &t : cititori) {
    t.join();
  }
  {
    std::lock_guard lk(tichete_mut);
    cititori_gata = true;
    tichete_cond.notify_all();
  }

  for (auto &t : preluatori) {
    t.join();
  }
  {
    for (int i = 0; i < 4; ++i) {
      tichete_locale_mut[i].lock();
    }
    preluatori_gata = true;
    for (int i = 0; i < 4; ++i) {
      tichete_locale_cond[i].notify_all();
      tichete_locale_mut[i].unlock();
    }
  }

  for (auto &t : serviciitori) {
    t.join();
  }
  
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
  elapsed /= 1'000'000'000;

  std::cout << "=== RAPORT SERVICII ===\n";
  {
    std::lock_guard lk(status_mut);
    for (const auto &entry : status) {
      std::cout << entry.first << " " << entry.second.serviciu << " ";
      for (const auto serviciu : entry.second.istoric) {
        std::cout << serviciu;
      }
      std::cout << "\n";
    }
  }

  std::cout << "=== TIMP TRECUT ===\n";
  std::cout << elapsed << "\n";

  return 0;
}

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <set>
#include <string>

#include <cctype>
#include <cstdlib>

using namespace std;

struct ScoreTotal {
  int id;
  int score;
  int country;
};

void on_new_row(
  list<ScoreTotal> &list,
  set<int> &cheaters,
  int id,
  int score,
  int country
) {
  if (cheaters.find(id) != cheaters.end()) {
    return;
  }

  ScoreTotal score_total {
    id,
    0,
    country,
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
}

int main(int argc, char **argv) {
  // cli arguments
  string data_dir = argv[1];
  string dest_path = argv[2];
  string time_path = argv[3];

  // solution
  list<ScoreTotal> list;
  set<int> cheaters;
  
  chrono::steady_clock::time_point begin = chrono::steady_clock::now();
  for (auto const &dir_entry : filesystem::directory_iterator{data_dir}) {
    ifstream fin{dir_entry.path()};

    // parse out country
    int country;
    {
      string file_name = dir_entry.path().filename();
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
        on_new_row(list, cheaters, id, score, country);
      }
    }
  }

  {
    ofstream fout{dest_path};
    for (auto const score_total : list) {
      fout << score_total.id << "," << score_total.score << "," << score_total.country << "\n";
    }
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

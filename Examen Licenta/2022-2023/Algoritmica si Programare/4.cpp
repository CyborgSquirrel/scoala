#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Persoana {
private:
  string nume;
  string prenume;
  int varsta;
public:
  Persoana(
    string nume,
    string prenume,
    int varsta
  ) :
    nume(nume),
    prenume(prenume),
    varsta(varsta)
  {
    
  }

  string getNume() {
    return nume;
  }
  string getPrenume() {
    return prenume;
  }
  int getVarsta() {
    return varsta;
  }
};

typedef bool (*CmpFn)(Persoana&, Persoana&);

void sort(vector<Persoana> &p, CmpFn cmpFn, int lt, int rt) {
  int len = rt-lt;
  if (len <= 1) {
    return;
  }

  int mid = (lt+rt) / 2;
  sort(p, cmpFn, lt, mid);
  sort(p, cmpFn, mid, rt);

  vector<Persoana> q;
  {
    int i = lt;
    int j = mid;

    while (i < mid && j < rt) {
      bool s = cmpFn(p[i], p[j]);
      if (s) {
        q.push_back(p[i]);
        i++;
      } else {
        q.push_back(p[j]);
        j++;
      }
    }
    while (i < mid) {
      q.push_back(p[i]);
      i++;
    }
    while (j < rt) {
      q.push_back(p[j]);
      j++;
    }
  }

  for (int i = lt; i < rt; ++i) {
    p[i] = q[i-lt];
  }
}

bool sortByName(Persoana &lt, Persoana &rt) {
  return lt.getNume() < rt.getNume();
}

bool sortByVarsta(Persoana &lt, Persoana &rt) {
  return lt.getVarsta() < rt.getVarsta();
}

bool sortByVarstaAndNume(Persoana &lt, Persoana &rt) {
  if (lt.getVarsta() != rt.getVarsta()) {
    return lt.getVarsta() < rt.getVarsta();
  }
  return lt.getNume() < rt.getNume();
}

int main() {
  vector<Persoana> p = {
    Persoana("Popescu", "Ion", 30),
    Persoana("Ionescu", "Maria", 25),
    Persoana("Dumitrescu", "Andrei", 40),
    Persoana("Georgescu", "Elena", 35),
    Persoana("Marinescu", "Alexandru", 50),
    Persoana("Constantinescu", "Ana", 28),
    Persoana("Petrescu", "Mihai", 33),
    Persoana("Stoica", "Gabriela", 27)
  };

  sort(p, sortByName, 0, p.size());
  for (auto &pe : p) {
    cout << pe.getNume() << "\n";
  }
  
  sort(p, sortByVarsta, 0, p.size());
  for (auto &pe : p) {
    cout << pe.getVarsta() << "\n";
  }

  sort(p, sortByVarstaAndNume, 0, p.size());
  for (auto &pe : p) {
    cout << pe.getVarsta() << " " << pe.getNume() << "\n";
  }
  
  return 0;
}

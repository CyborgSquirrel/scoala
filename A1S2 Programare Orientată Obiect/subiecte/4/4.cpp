#include <vector>
#include <iostream>

using namespace std;

template <typename T>
class Expresie {
private:
	T a;
	vector<T> op;
public:
	Expresie(T a) : a(a) { }
	T valoare() {
		T b = a;
		for (const auto &c : op) {
			b += c;
		}
		return b;
	}
	Expresie &undo() {
		op.pop_back();
		return *this;
	}
	Expresie &operator+(int b) {
		op.push_back(b);
		return *this;
	}
	Expresie &operator-(int b) {
		op.push_back(-b);
		return *this;
	}
};

void operatii() {
  Expresie<int> exp{3}; // construim o expresie,pornim cu operandul 3
  // se extinde expresia in dreapta cu operator (+ sau -)  si operand
  exp = exp + 7 + 3;
  exp = exp - 8;
  // tipareste valoarea expresiei (in acest caz:5 rezultat din 3+7+3-8)
  cout << exp.valoare() << "\n";
  exp.undo(); // reface ultima operatie efectuata
  // tipareste valoarea expresiei (in acest caz:13 rezultat din 3+7+3)
  cout << exp.valoare() << "\n";
  exp.undo().undo();
  cout << exp.valoare() << "\n"; // tipareste valoarea expresiei (in acest
                                 // caz:3)
}

int main() {
	operatii();
}

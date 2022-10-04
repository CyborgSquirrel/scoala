#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Examen {
private:
	string ce, cand;
public:
	Examen(const string &ce, const string &cand)
	: ce(ce), cand(cand)
	{ }
	string getDescriere() const {
		return ce + " ora " + cand;
	}
};

template <typename T>
class ToDo {
private:
	vector<T> v;
public:
	ToDo &operator<<(const T &t) {
		v.push_back(t);
		return *this;
	}
	void printToDoList(ostream &os) {
		bool b = false;
		for (const auto &t : v) {
			if (b) cout << ";";
			else b = true;
			cout << t.getDescriere();
		}
	}
};

void todolist() {
	ToDo<Examen> todo;
	Examen oop{"oop scris", "8:00"};
	todo << oop << Examen{"oop practic", "11:00"}; // Adauga 2 examene la todo
	std::cout << oop.getDescriere(); // tipareste la consola: oop scris ora 8:00
	// itereaza elementele adaugate si tipareste la consola lista de activitati
	// in acest caz tipareste: De facut:oop scris ora 8:00;oop practic ora 11:00
	todo.printToDoList(cout);
}

int main() {
	todolist();
	return 0;
}

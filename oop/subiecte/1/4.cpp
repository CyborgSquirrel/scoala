#include <vector>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Geanta {
private:
	string utilizator;
	vector<T> v;
public:
	Geanta(string utilizator)
	: utilizator(utilizator)
	{ }
	Geanta operator+(T o) {
		Geanta g = *this;
		g.v.push_back(o);
		return g;
	}
	typename vector<T>::iterator begin() {
		return v.begin();
	}
	typename vector<T>::iterator end() {
		return v.end();
	}
};

void calatorie() { 
	Geanta<string> ganta{ "Ion" };//creaza geanta pentru Ion 
	ganta = ganta + string{ "haine" }; //adauga obiect in ganta 
	ganta + string{ "pahar" };
	for (auto o : ganta) {
		cout << o << "\n";
	}
}

int main() {
	calatorie();
	return 0;
}

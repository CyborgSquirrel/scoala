#include <vector>
#include <cassert>

// Functia gaseste cel mai mare, si al doilea cel mai mare numar, din vectorul l furnizat.
// Daca l are mai putin de doua elemente, va fi aruncata o exceptie.
// in: l -- vectorul, in care se va cauta cel mai mare, si al doilea cel mai mare numar
// out: o pereche, primul element este cel mai mare numar, iar al doilea element este al doilea cel mai mare numar
 
std::pair<int, int> f(std::vector<int> l) {
	if (l.size() < 2)
		throw std::exception{};
	std::pair<int, int> rez{-1, -1};
	for (auto el : l) {
		if (el < rez.second)
			continue;
		if (rez.first < el) {
			rez.second = rez.first;
			rez.first = el;
		} else {
			rez.second = el;
		}
	}
	return rez;
}

void test_f() {
	std::vector<int> v1 { 4, 74, 42, 12, 75, 23, 56, 91 };
	std::pair<int, int> a1 { 91, 75 };
	assert(f(v1) == a1);
	
	try {
		std::vector<int> v2;
		v2.push_back(1);
		f(v2);
		assert(false);
	} catch (std::exception &ex) {
		
	}
}

int main() {
	test_f();
	return 0;
}

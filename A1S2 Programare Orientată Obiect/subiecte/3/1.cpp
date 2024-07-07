#include <stdexcept>
#include <cassert>
#include <cstring>

// Functia verifica daca a este prim.
// Daca a este un numar negativ, se arunca o exceptie.
// in: a -- numarul pentru care se verifica daca este prim
// out: true, daca a este prim, false altfel
bool f(int a) {
  if (a <= 0)
    throw std::runtime_error("Illegal argument");
  int d = 2;
  while (d < a && a % d > 0)
    d++;
  return d >= a;
}

void test_f() {
	try {
		f(-5);
		assert(false);
	} catch (const std::runtime_error &ex) {
		assert(strcmp(ex.what(), "Illegal argument") == 0);
	}
	
	assert(f(5));
	assert(!f(6));
	assert(f(7));
	assert(!f(8));
	assert(f(17));
	assert(!f(100));
}

int main() {
	test_f();
	return 0;
}

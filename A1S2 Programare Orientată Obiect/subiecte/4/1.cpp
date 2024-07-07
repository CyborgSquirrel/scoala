#include <cstring>
#include <cassert>

// Functia determina daca a este numar prim.
// Daca a este <= 1, se va arunca o exceptie.
// in: a -- numarul, pentru care se va determina daca este prim sau nu
// out: true, daca a este prim, false altfel
bool f(int a) {
  if (a <= 1)
    throw "Illegal argument";
  int aux = 0;
  for (int i = 2; i < a; i++) {
    if (a % i == 0) {
      aux++;
    }
  }
  return aux == 0;
} 

void test_f() {
	try {
		f(-2);
		assert(false);
	} catch (const char *ex) {
		assert(strcmp(ex, "Illegal argument") == 0);
	}
	assert(f(2));
	assert(f(3));
	assert(!f(4));
	assert(f(5));
	assert(!f(100));
	assert(f(17));
}

int main() {
	test_f();
	return 0;
}

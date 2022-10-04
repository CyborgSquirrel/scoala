#include <iostream>
#include <vector>
#include <cassert>
#include <string>

using namespace std;

class MyException {
public:
	MyException(const char *s) { }
};

vector<int> f(int a) {
	if (a < 0)
		throw MyException{"Illegal argument"};
	vector<int> rez;
	for (int i = 1; i <= a; i++) {
		if (a % i == 0) {
			rez.push_back(i);
		}
	}
	return rez;
}

void test_f() {
	try {
		f(-4);
		assert(false);
	} catch (MyException &ex) {
		
	}
	
	std::vector<int> s1 { 1, 2, 3, 4, 6, 8, 12, 24 };
	assert(f(24) == s1);
	
	std::vector<int> s2 { 1, 5, 25 };
	assert(f(25) == s2);
	
	std::vector<int> s3 { 1, 2, 3, 6 };
	assert(f(6) == s3);
}

int main() {
	test_f();
	return 0;
}

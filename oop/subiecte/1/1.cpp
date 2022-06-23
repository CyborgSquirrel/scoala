#include <stdexcept>
#include <cassert>

using namespace std;

int f(int x) { 
	if (x <= 0) 
		throw std::runtime_error("Invalid argument!"); 
	
	int rez = 0; 
	while (x) 
	{ 
		rez = rez * 10 + x % 10; 
		x /= 10; 
	} 
	return rez; 
} 

void test_f() {
	try {
		f(-5);
		assert(false);
	} catch (const std::runtime_error &ex) {
		
	}
	assert(f(12) == 21);
	assert(f(4532) == 2354);
	assert(f(642) == 246);
}

int main() {
	test_f();
}

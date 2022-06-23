#include <iostream> 
using namespace std; 
class A { 
public: 
 A() {cout << "A" << endl;} 
 ~A() {cout << "~A" << endl; 
} 
 void print() {cout << "print" << endl;} 
};

void f() {
	A a[2];
	a[1].print();
}

int main() {
	f();
}

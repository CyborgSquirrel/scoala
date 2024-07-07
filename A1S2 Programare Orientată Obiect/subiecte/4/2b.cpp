// 2 b  (0.5p)
#include <iostream>
using namespace std;
class A {
public:
  A() { cout << "A" << endl; }
  ~A() { cout << "~A" << endl; }
  void print() { cout << "print" << endl; }
};
void f() {
  A a[2];
  a[0].print();
}
int main() {
	f();
	return 0;
}

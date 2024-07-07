// 2 a  (1p)
#include <iostream>
using namespace std;
class A {
public:
  A() { cout << "A()" << endl; }
  void print() { cout << "printA" << endl; }
};
class B : public A {
public:
  B() { cout << "B()" << endl; }
  void print() { cout << "printB" << endl; }
};
int main() {
  A *o1 = new A();
  B *o2 = new B();
  o1->print();
  o2->print();
  delete o1;
  delete o2;
  return 0;
}

// 2 b  (0.5p)
#include <iostream>
using namespace std;
class A {
  int x;

public:
  A(int x) : x{x} {}
  void print() { cout << x << endl; }
};
A f(A a) {
  a.print();
  a = A{10};
  a.print();
  return a;
}
int main() {
  A a{4};
  a.print();
  f(a);
  a.print();
}

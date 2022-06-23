//2 a  (1p) 
#include <iostream>
#include <vector>
struct A {
  A() { std::cout << "A"; }
  virtual void print() { std::cout << "A"; }
};
struct B : public A {
  B() { std::cout << "B"; }
  void print() override { std::cout << "B"; }
};
int main() {
  std::vector<A> v;
  v.push_back(A{});
  v.push_back(B{});
  for (auto &el : v)
    el.print();
  return 0;
}

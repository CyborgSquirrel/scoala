#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MyObject {
public:
  virtual ~MyObject() { };
  virtual void print() = 0;
};

class MyInteger : public MyObject {
private:
  int a;
public:
  MyInteger(int a) : a(a) { }
  ~MyInteger() override {};
  void print() override {
    cout << a << " ";
  }
};

class MyString : public MyObject {
private:
  string s;
public:
  MyString(char *s) : s(s) { }
  ~MyString() override {};
  void print() override {
    cout << s << " ";
  }
};

class MyObjectList {
private:
  vector<MyObject*> list;
public:
  MyObjectList &add(MyObject *myObject) {
    list.push_back(myObject);
    return *this;
  }
  int size() {
    return list.size();
  }
  MyObject *at(int i) {
    return this->list[i];
  }
};

class MyListIterator {
private:
  MyObjectList &list;
  int i;
public:
  MyListIterator(MyObjectList &list) : list(list), i(0) { }
  bool isValid() {
    return i < list.size();
  }
  MyObject *element() {
    return list.at(i);
  }
  void next() {
    i += 1;
  }
};

void function() {
  MyObjectList list{};
  list.add(new MyInteger{ 2 }).add(new MyString{ "Hi" });
  MyString* s = new MyString{ "Bye" };
  list.add(s).add(new MyString{ "5" });
  MyListIterator i{ list };
  while (i.isValid()) {
    MyObject* o = i.element();
    o->print();
    i.next();
  } // prints: 2 Hi Bye 5
}

int main() {
  function();
  
  return 0;
}

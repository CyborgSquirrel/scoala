#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class Measurement {
private:
	int a;
public:
	Measurement(int a) : a(a) { }
	int value() const { return a; }
	bool operator<(const Measurement<T> &rhs) const {
		return a < rhs.a;
	}
	Measurement &operator+(int b) {
		a += b;
		return *this;
	}
};

int main() {
  // creaza un vector de masuratori cu valorile (10,2,3)
  std::vector<Measurement<int>> v{10, 2, 3};
  v[2] + 3 + 2;                  // aduna la masuratoarea 3 valuarea 5
  std::sort(v.begin(), v.end()); // sorteaza masuratorile
  // tipareste masuratorile (in acest caz: 2,8,10)
  for (const auto &m : v)
    std::cout << m.value() << ",";
  return 0;
}

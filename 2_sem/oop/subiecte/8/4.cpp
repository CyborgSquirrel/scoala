#include <algorithm>
#include <vector>

template <typename T>
class Measurement {
private:
	T a;
public:
	Measurement(T a) : a(a) { }
};

int main() {
	// creaza un vector de masuratori cu valorile (10,2,3)
	std::vector<Measurement<int>> v{10, 2, 3};
	// v[2] + 3 + 2;                  // aduna la masuratoarea 3 valuarea 5
	// std::sort(v.begin(), v.end()); // sorteaza masuratorile
	// // tipareste masuratorile (in acest caz: 2,8,10)
	// for (const auto &m : v)
	// 	std::cout << m.value() << ",";
	// return 0;
}

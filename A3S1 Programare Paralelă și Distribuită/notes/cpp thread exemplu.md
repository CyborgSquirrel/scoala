```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <thread>
#include <vector>

void my_thread(int a, std::vector<int> &v) {
	for (int i = 0; i < a; ++i) {
		v.push_back(i);
	}
}

int main() {
	std::vector<int> v;
	std::thread t(my_thread, 10, std::ref(v));
	t.join();

	for (const auto a : v) {
		std::cout << a << "\n";
	}

	return 0;
}

```
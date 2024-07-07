```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <thread>
#include <condition_variable>

class S {
	std::mutex m;
	std::condition_variable c;
	int v;
public:
	S() : m(), c(), v(0) {}
	void P() {
		std::unique_lock lk {m};
		c.wait(lk, [this](){ return this->v > 0; });
		v--;
	}
	void V() {
		v++;
	}
};

void worker(int &v, S &s) {
	s.P();
	v += 1;
	s.V();
}

int main() {
	int v = 0;
	S s;
	s.V();

	std::thread t1(worker, std::ref(v), std::ref(s));
	std::thread t2(worker, std::ref(v), std::ref(s));

	t1.join();
	t2.join();

	std::cout << v << std::endl;

	return 0;
}
```
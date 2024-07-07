```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <future>
#include <vector>

const int N = 10'000;

int async_sum(std::vector<int> &arr, int start, int end) {
	int len = end - start;
	if (len <= 100) {
		int sum = 0;
		for (int i = start; i <= end; ++i) {
			sum += arr[i];
		}
		return sum;
	}

	int mid = start + len/2;
	auto lt_handle = std::async(std::launch::async, async_sum, std::ref(arr), start, mid-1);
	auto rt_handle = std::async(std::launch::async, async_sum, std::ref(arr), mid, end);
	return lt_handle.get() + rt_handle.get();
}

int main() {
	std::vector<int> arr;
	arr.reserve(N);
	for (int i = 0; i < N; ++i) {
		arr.push_back(i);
	}
	int sum = async_sum(arr, 0, arr.size()-1);
	std::cout << "sum = " << sum << std::endl;

	return 0;
}
```
https://www.geeksforgeeks.org/bubble-sort-algorithm/

```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

void bubble_sort(vector<int> &v) {
	for (int i = 0; i < v.size() - 1; ++i) {
		for (int j = 1; j < v.size() - i; ++j) {
			if (v[j-1] > v[j]) {
				swap(v[j-1], v[j]);
			}
		}
	}
}

int main() {
	vector<int> v { 7, 2, 4, 8, 5 };
	bubble_sort(v);
	for (const auto a : v) {
		cout << a << endl;
	}

	return 0;
}
```
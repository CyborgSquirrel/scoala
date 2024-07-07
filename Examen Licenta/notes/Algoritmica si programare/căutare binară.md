```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

int binary_search(vector<int> &v, int a) {
	int lt = 0;
	int rt = v.size()-1;
	while (lt <= rt) {
		int mid = (lt+rt)/2;
		if (v[mid] == a) {
			return mid;
		} else if (a < v[mid]) {
			rt = mid-1;
		} else if (v[mid] < a) {
			lt = mid+1;
		}
	}
	return -1;
}

void s(vector<int> &v, int a) {
	cout << a << std::flush << " " << binary_search(v, a) << endl;
}

int main() {
	vector<int> v { 4, 6, 8, 12, 15 };

	for (int i = 0; i < 2; ++i) {
		if (v.size() % 2 == 0) {
			cout << "Even length" << endl;
		} else {
			cout << "Odd length" << endl;
		}
		
		s(v, v.front()-1);
		for (const auto a : v) {
			s(v, a);
		}
		s(v, v.back()+1);
		s(v, 9);

		v.pop_back();
	}

	return 0;
}
```
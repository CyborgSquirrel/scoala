```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

void mergesort(
	vector<int> &v,
	int lt, int rt
) {
	if (lt >= rt-1) {
		return;
	}

	int mid = (lt+rt) / 2;
	mergesort(v, lt, mid);
	mergesort(v, mid, rt);

	vector<int> q;
	{
		int i = lt;
		int j = mid;
		while (i < mid && j < rt) {
			if (v[i] < v[j]) {
				q.push_back(v[i]);
				i++;
			} else {
				q.push_back(v[j]);
				j++;
			}
		}
	
		while (i < mid) {
			q.push_back(v[i]);
			i++;
		}
		while (j < rt) {
			q.push_back(v[j]);
			j++;
		}
	}

	for (int i = lt; i < rt; ++i) {
		v[i] = q[i-lt];
	}
}

int main() {
	vector<int> v { 7, 2, 4, 8, 5 };
	mergesort(v, 0, v.size());
	for (const auto a : v) {
		cout << a << endl;
	}
	return 0;
}

```
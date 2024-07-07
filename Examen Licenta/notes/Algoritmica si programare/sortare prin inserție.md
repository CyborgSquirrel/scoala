Jumătatea din stânga a listei este mereu sortată. La fiecare pas, se **inserează** primul element din jumătatea dreaptă a listei la locul lui corespunzător în jumătatea stângă.

https://www.geeksforgeeks.org/insertion-sort/

```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

void insertion_sort(vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		int j = i;
		int tmp = v[j];
		while (j >= 1 && v[j] < v[j-1]) {
			v[j] = v[j-1];
			j--;
		}
		v[j] = tmp;
	}
}

int main() {
	vector<int> v { 7, 2, 4, 8, 5 };
	insertion_sort(v);
	for (const auto a : v) {
		cout << a << endl;
	}
	return 0;
}
```
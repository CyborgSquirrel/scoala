Primul element este minimul din întreaga listă, al doilea este minimul din lista fără primul element, al treilea este minimul din lista fără primele două elemente, etc..

Jumătatea din stânga a listei este mereu sortată. La fiecare pas, se **selectează** elementul minim din jumătatea dreaptă a listei, și se adaugă la sfârșitul jumătății stângi.

https://www.geeksforgeeks.org/selection-sort/

```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

void selection_sort(vector<int> &v) {
	for (int i = 0; i < v.size(); ++i) {
		int min_index = i;
		for (int j = i+1; j < v.size(); ++j) {
			if (v[j] < v[min_index]) {
				min_index = j;
			}
		}
		swap(v[i], v[min_index]);
	}
}

int main() {
	vector<int> v { 7, 2, 4, 8, 5 };
	selection_sort(v);
	for (const auto a : v) {
		cout << a << endl;
	}
	return 0;
}
```
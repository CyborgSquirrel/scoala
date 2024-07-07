Operația `partition` este cea mai importantă. La fiecare pas, se alege un pivot; toate elementele mai mici decât acest pivot se mută în stânga, unul câte unul. Apoi pivotul se mută fix după elementele mai mici decât el.

Așadar, în stânga pivotului sunt toate elementele mai mici decât el, iar în dreapta lui sunt toate elementele mai mari decât el. Pivotul se află fix în locul corect din listă!

Operația `partition` se repetă pe elementele din stânga și din dreapta pivotului, ș.a.m.d..

https://www.geeksforgeeks.org/quick-sort-algorithm/

```cpp
// run {"compiler": "cpp"}

#include <iostream>
#include <vector>

using namespace std;

int partition(
	vector<int> &v,
	int lt, int rt,
	int pivot
) {
	int j = lt;
	for (int i = lt; i < rt; ++i) {
		if (v[i] < v[pivot]) {
			swap(v[i], v[j]);
			if (j == pivot) {
				pivot = i;
			}
			j++;
		}
	}

	swap(v[j], v[pivot]);
	pivot = j;
	
	return pivot;
}

void quicksort(
	vector<int> &v,
	int lt, int rt
) {
	if (lt >= rt) {
		return;
	}

	int pivot = partition(v, lt, rt, rt-1);
	quicksort(v, lt, pivot);
	quicksort(v, pivot+1, rt);
}

int main() {
	vector<int> v { 7, 2, 4, 8, 5 };
	quicksort(v, 0, v.size());
	for (const auto a : v) {
		cout << a << endl;
	}
	return 0;
}
```
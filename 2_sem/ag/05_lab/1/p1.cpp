#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int N = 100041;

int n;
int p[N], c[N];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin >> p[i];
		if (p[i] != -1) c[p[i]]++;
	}
	
	priority_queue<int, std::vector<int>, std::greater<int>> pq;
	for (int i = 0; i < n; ++i) {
		if (c[i] == 0) pq.push(i);
	}
	
	fout << n-1 << "\n";
	for (int i = 1; i < n; ++i) {
		int a = pq.top(); pq.pop();
		fout << p[a] << " ";
		c[p[a]]--;
		if (c[p[a]] == 0) pq.push(p[a]);
	}
	
	return 0;
}

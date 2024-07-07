#include <iostream>
#include <fstream>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

const int M = 100041;
int m;

int f[M];
int c[M];
int tre[M];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> m;
	for (int i = 0; i < m; ++i) {
		tre[i] = -1;
	}
	
	for (int i = 0; i < m; ++i) {
		int a;
		fin >> a;
		c[i] = a;
		f[a]++;
	}
	
	auto cmp = [](int a, int b) { return a > b; };
	priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
	for (int i = 0; i < m+1; ++i) {
		if (f[i] == 0) {
			q.push(i);
		}
	}
	
	for (int i = 0; i < m; ++i) {
		int a = q.top(); q.pop(); f[a]++;
		int b = c[i]; f[b]--;
		if (f[b] == 0) {
			q.push(b);
		}
		tre[a] = b;
	}
	
	fout << m+1 << endl;
	for (int i = 0; i < m+1; ++i) {
		fout << tre[i] << " ";
	}
	
	return 0;
}

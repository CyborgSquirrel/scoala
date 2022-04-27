#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int N = 100041;

int n;
int v[N], f[N];
int p[N];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin >> v[i];
		f[v[i]]++;
	}
	
	set<int> se;
	for (int i = 0; i < n+1; ++i) {
		p[i] = -1;
		if (f[i] == 0) se.insert(i);
	}
	
	for (int i = 0; i < n; ++i) {
		p[*se.begin()] = v[i];
		se.erase(se.begin());
		f[v[i]]--;
		if (f[v[i]] == 0) se.insert(v[i]);
	}
	
	fout << n+1 << "\n";
	for (int i = 0; i < n+1; ++i) {
		fout << p[i] << " ";
	}
	
	return 0;
}

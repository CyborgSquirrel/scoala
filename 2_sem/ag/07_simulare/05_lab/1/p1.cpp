#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int N = 100041;
int n;
int gra[N];
int tre[N];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> n;
	for (int i = 0; i < n; ++i) {
		int a;
		fin >> a;
		tre[i] = a;
		if (a != -1) {
			gra[a]++;
		}
	}
	
	auto cmp = [](int lhs, int rhs) { return lhs > rhs; };
	priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
	for (int i = 0; i < n; ++i) {
		if (gra[i] == 0) {
			q.push(i);
		}
	}
	
	fout << n-1 << endl;
	while (!q.empty()) {
		int a = q.top(); q.pop();
		if (tre[a] != -1) {
			fout << tre[a] << " ";
			gra[tre[a]]--;
			if (gra[tre[a]] == 0) {
				q.push(tre[a]);
			}
		}
	}
	
	return 0;
}

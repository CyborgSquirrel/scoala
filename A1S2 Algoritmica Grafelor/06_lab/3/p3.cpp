#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

const int V = 101041;
const int E = 501041;

int v, e;

vector<int> gra[V];
int g[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	for (int i = 0; i < e; ++i) {
		int a, b;
		fin >> a >> b;
		gra[a].push_back(b); g[a]++;
		gra[b].push_back(a); g[b]++;
	}
	
	int src = 0;
	while (g[src] == 0) src++;
	
	vector<int> st;
	st.push_back(src);
	while (!st.empty()) {
		int a = st.back();
		if (g[a] == 0) {
			if (st.size() != 1) fout << a << " ";
			st.pop_back();
		} else {
			int b = gra[a].front();
			gra[a].erase(gra[a].begin());
			gra[b].erase(find(gra[b].begin(), gra[b].end(), a));
			g[a]--;
			g[b]--;
			st.push_back(b);
		}
	}
	
	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int V = 101041;
const int E = 501041;

int v, e;
vector<int> adj[V];
int gra[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	for (int i = 0; i < e; ++i) {
		int a, b;
		fin >> a >> b;
		adj[a].push_back(b); gra[a]++;
		adj[b].push_back(a); gra[b]++;
	}
	
	int a = 0;
	while (gra[a] == 0) a++;
	
	stack<int> s;
	s.push(a);
	while (!s.empty()) {
		int a = s.top();
		if (gra[a] > 0) {
			bool found_b = false;
			int b = adj[a][0];
			s.push(b);
			adj[a].erase(find(adj[a].begin(), adj[a].end(), b)); gra[a]--;
			adj[b].erase(find(adj[b].begin(), adj[b].end(), a)); gra[b]--;
		} else {
			if (s.size() != 1) fout << a << " ";
			s.pop();
		}
	}
	
	return 0;
}

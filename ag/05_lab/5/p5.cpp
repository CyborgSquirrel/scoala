#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
	int a, b;
	int v;
};

const int N = 5041;
const int M = 50041;

int n, m;
vector<Edge> es;

vector<pair<int, int>> ans;

int p[N];
int parent(int a) {
	if (p[a] != a) {
		p[a] = parent(p[a]);
	}
	return p[a];
}
void unite(int a, int b) {
	a = parent(a);
	b = parent(b);
	p[b] = a;
}
bool check(int a, int b) {
	return parent(a) == parent(b);
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> n >> m;
	for (int i = 0; i < m; ++i) {
		Edge edge;
		fin >> edge.a >> edge.b >> edge.v;
		es.push_back(edge);
	}
	
	auto cmp = [](const Edge &lhs, const Edge &rhs){ return lhs.v < rhs.v; };
	sort(es.begin(), es.end(), cmp);
	for (int i = 0; i < n; ++i) p[i] = i;
	
	int sum = 0;
	for (auto e : es) {
		if (!check(e.a, e.b)) {
			unite(e.a, e.b);
			sum += e.v;
			ans.push_back({e.a, e.b});
		}
	}
	sort(ans.begin(), ans.end());
	
	fout << sum << "\n";
	fout << ans.size() << "\n";
	for (auto e : ans) {
		fout << e.first << " " << e.second << "\n";
	}
	
	return 0;
}

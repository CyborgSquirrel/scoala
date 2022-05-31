#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

struct Edge {
	int b, v;
};

struct Node {
	int a, v;
};
bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.v < rhs.v || (lhs.v == rhs.v && lhs.a < rhs.a);
}

const int INF = 0x3f3f3f3f;
const int N = 50041;

int n, m;
vector<Edge> gra[N];
int d[N];

int main() {
	fin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, v;
		fin >> a >> b >> v;
		gra[a].push_back({b, v});
	}
	
	for (int i = 1; i <= n; ++i) {
		d[i] = INF;
	}
	
	set<Node> se;
	d[1] = 0;
	se.insert({1, 0});
	while (!se.empty()) {
		auto node = *se.begin(); se.erase(se.begin());
		for (auto edge : gra[node.a]) {
			if (d[node.a] + edge.v < d[edge.b]) {
				if (d[edge.b] != INF) {
					se.erase({edge.b, d[edge.b]});
				}
				d[edge.b] = d[node.a] + edge.v;
				se.insert({edge.b, d[node.a] + edge.v});
			}
		}
	}
	
	for (int i = 2; i <= n; ++i) {
		fout << ((d[i] < INF) ? d[i] : 0) << " ";
	}
	
	return 0;
}

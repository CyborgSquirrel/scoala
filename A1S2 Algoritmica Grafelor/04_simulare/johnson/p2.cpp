#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

struct Edge {
	int b, v;
};
struct EdgeIndex {
	int a, i;
};
struct Node {
	int a, v;
};
bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.v < rhs.v || (lhs.v == rhs.v && lhs.a < rhs.a);
}

const int INF = 0x3f3f3f3f;
const int N = 2041;

int n, m;
vector<Edge> gra[N];
vector<EdgeIndex> eind;

int h[N], c[N];
bool inq[N];

int d[N][N];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, v;
		fin >> a >> b >> v;
		eind.push_back({a, (int) gra[a].size()});
		gra[a].push_back({b, v});
	}
	
	// introducem pseudo-nod
	for (int i = 0; i < n; ++i) {
		gra[n].push_back({i, 0});
	}
	
	// bellman-ford din pseudo-nod
	bool negative_cycle = false;
	for (int i = 0; i < n; ++i) { h[i] = INF; }
	queue<int> q;
	q.push(n);
	inq[n] = true;
	h[n] = 0;
	while (!q.empty() && !negative_cycle) {
		int a = q.front(); q.pop();
		inq[a] = false;
		for (auto e : gra[a]) {
			if (h[a] + e.v < h[e.b]) {
				h[e.b] = h[a] + e.v;
				if (!inq[e.b]) {
					inq[e.b] = true;
					q.push(e.b);
				}
				c[e.b]++;
				if (c[e.b] >= n+1) { negative_cycle = true; }
			}
		}
	}
	
	if (negative_cycle) {
		fout << -1 << "\n";
	} else {
		// reponderare
		for (int i = 0; i < n; ++i) {
			for (auto &e : gra[i]) {
				e.v += h[i] - h[e.b];
			}
		}
		for (auto ei : eind) {
			auto &e = gra[ei.a][ei.i];
			fout << ei.a << " " << e.b << " " << e.v << "\n";
		}
		
		// dijkstra
		for (int start = 0; start < n; ++start) {
			int *sd = d[start];
			for (int i = 0; i < n; ++i) {
				sd[i] = INF;
			}
			sd[start] = 0;
			set<Node> s;
			s.insert({start, 0});
			while (!s.empty()) {
				Node node = *s.begin(); s.erase(s.begin());
				for (auto e : gra[node.a]) {
					if (node.v + e.v < sd[e.b]) {
						if (sd[e.b] != INF) {
							s.erase({e.b, sd[e.b]});
						}
						sd[e.b] = node.v + e.v;
						s.insert({e.b, node.v + e.v});
					}
				}
			}
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (d[i][j] != INF) fout << d[i][j]-h[i]+h[j] << " ";
				else                fout << "INF" << " ";
			}
			fout << "\n";
		}
	}
	
	return 0;
}

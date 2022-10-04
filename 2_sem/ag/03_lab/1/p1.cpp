#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
	int b, w;
};

struct Node {
	int a, d;
};
bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.d < rhs.d || (lhs.d == rhs.d && lhs.a < rhs.a);
}

const int V = 10041;
const int INF = 0X3F3F3F3F;

int v, e, s;
vector<Edge> g[V];
int d[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e >> s;
	for (int i = 0; i < e; ++i) {
		int a, b, w;
		fin >> a >> b >> w;
		g[a].push_back({b, w});
	}
	
	for (int i = 0; i < v; ++i) {
		d[i] = INF;
	}
	d[s] = 0;
	
	priority_queue<Node> pq;
	pq.push({s, d[s]});
	while (!pq.empty()) {
		Node n = pq.top();
		pq.pop();
		if (n.d > d[n.a]) continue;
		for (auto m : g[n.a]) {
			if (n.d + m.w < d[m.b]) {
				d[m.b] = n.d + m.w;
				pq.push({m.b, d[m.b]});
			}
		}
	}
	
	for (int i = 0; i < v; ++i) {
		if (d[i] == INF) fout << "INF ";
		else fout << d[i] << " ";
	}
	
	fin.close();
	fout.close();
	
	return 0;
}

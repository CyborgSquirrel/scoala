#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct BfEdge { int a, b, w; };
struct DkEdge { int b, w; };
struct DkNode { int a, d; };
bool operator<(const DkNode &lhs, const DkNode &rhs) {
	return lhs.d < rhs.d || (lhs.d == rhs.d && lhs.a < rhs.a);
}

const int V = 1041;
const int INF = 0X3F3F3F3F;

int v, e;
vector<BfEdge> es;
int h[V];

vector<DkEdge> g[V];
int d[V][V];

void solve(istream &in, ostream &out) {
	in >> v >> e;
	for (int i = 0; i < e; ++i) {
		int a, b, w;
		in >> a >> b >> w;
		es.push_back({a, b, w});
	}
	
	// bellman ford
	for (int i = 0; i < v; ++i) {
		h[i] = INF;
		es.push_back({v, i, 0});
	}
	h[v] = 0;
	for (int i = 1; i < v; ++i) {
		for (auto ev : es) {
			if (h[ev.a] + ev.w < h[ev.b]) {
				h[ev.b] = h[ev.a] + ev.w;
			}
		}
	}
	bool ok = true;
	for (auto ev : es) {
		if (h[ev.a] + ev.w < h[ev.b]) {
			ok = false;
			break;
		}
	}
	
	// ciclu negativ
	if (!ok) {
		out << -1;
		return;
	}
	
	// reponderare
	for (int i = 0; i < e; ++i) {
		auto &bev = es[i];
		DkEdge dev = {bev.b, bev.w + h[bev.a] - h[bev.b]};
		g[bev.a].push_back(dev);
		out << bev.a << " " << bev.b << " " << dev.w << "\n";
	}
	
	// dijkstra
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j < v; ++j) {
			if (i != j) {
				d[i][j] = INF;
			} else {
				d[i][j] = 0;
			}
		}
	}
	
	priority_queue<DkNode> pq;
	for (int s = 0; s < v; ++s) {
		pq.push({s, d[s][s]});
		while (!pq.empty()) {
			DkNode n = pq.top();
			pq.pop();
			if (n.d > d[s][n.a]) continue;
			for (auto ev : g[n.a]) {
				if (n.d + ev.w < d[s][ev.b]) {
					d[s][ev.b] = n.d + ev.w;
					pq.push({ev.b, d[s][ev.b]});
				}
			}
		}
	}
	
	for (int i = 0; i < v; ++i) {
		for (int j = 0; j < v; ++j) {
			if (d[i][j] != INF) out << d[i][j] + h[j] - h[i] << " ";
			else out << "INF ";
		}
		out << "\n";
	}
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	solve(fin, fout);
	
	fin.close();
	fout.close();
	
	return 0;
}

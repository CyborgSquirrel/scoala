#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct Edge { int b, v; };
struct Node { int a, v; };
bool operator<(const Node &lhs, const Node &rhs) {
	return lhs.v < rhs.v || (lhs.v == rhs.v && lhs.a < rhs.a);
}

// ifstream fin("data.in");
ifstream fin("data.in");
ofstream fout("data.out");

const int INF = 0x3f3f3f3f;
const int N = 10041;
vector<Edge> gra[N];

int n;
int x, y;
int d[N], p[N];

int main() {
	fin >> n >> x >> y;
	for (int i = 0; i < n; ++i) {
		int a, b, v;
		fin >> a >> b >> v;
		gra[a].push_back({b, v});
	}
	
	for (int i = 0; i <= N; ++i) {
		d[i] = INF;
		p[i] = -1;
	}
	set<Node> s;
	d[x] = 0;
	s.insert({x, 0});
	while (!s.empty()) {
		auto node = *s.begin(); s.erase(s.begin());
		for (auto edge : gra[node.a]) {
			if (node.v + edge.v < d[edge.b]) {
				if (d[edge.b] != INF) {
					s.erase({edge.b, d[edge.b]});
				}
				d[edge.b] = node.v + edge.v;
				p[edge.b] = node.a;
				s.insert({edge.b, node.v + edge.v});
			}
		}
	}
	
	stack<int> path;
	int node = y;
	while (node != -1) {
		path.push(node);
		node = p[node];
	}
	
	if (path.empty() || path.top() != x) {
		fout << "Nu exista!";
	} else {
		while (!path.empty()) {
			fout << path.top();
			path.pop();
			if (!path.empty()) fout << " -> ";
		}
	}
	
	return 0;
}

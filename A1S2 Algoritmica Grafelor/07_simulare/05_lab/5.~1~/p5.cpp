#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int INF = 0x3F3F3F3F;

const int V = 5041;
const int E = 50041;

struct Node {
	int a, key;
};
struct Edge {
	int a, b, w;
	int oth(int x) {
		if (x == a) return b;
		else if (x == b) return a;
		else return -1;
	}
};

Edge edges[E];

int v, e;
vector<int> edg[V];
int key[V];
bool vi[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	for (int i = 0; i < v; ++i) {
		key[i] = -1;
	}
	
	for (int i = 0; i < e; ++i) {
		Edge &ec = edges[i];
		fin >> ec.a >> ec.b >> ec.w;
		edg[ec.a].push_back(i);
		edg[ec.b].push_back(i);
	}
	
	int cost = 0;
	auto cmp = [](const Node &lhs, const Node &rhs) { return !(lhs.key < rhs.key); };
	priority_queue<Node, vector<Node>, decltype(cmp)> q(cmp);
	q.push({ 0, key[0] });
	while (!q.empty()) {
		Node nc = q.top(); q.pop();
		int a = nc.a;
		if (!vi[a]) {
			if (key[a] != -1) {
				cost += edges[key[a]].w;
			}
			vi[a] = true;
			for (auto ei : edg[a]) {
				auto &ec = edges[ei];
				int b = ec.oth(a);
				if (!vi[b]) {
					if (key[b] == -1 || ec.w < edges[key[b]].w) {
						key[b] = ei;
						q.push({ b, ec.w });
					}
				}
			}
		}
	}
	
	vector<pair<int, int>> ans;
	for (int i = 1; i < v; ++i) {
		auto ec = edges[key[i]];
		pair<int, int> p;
		if (ec.a < ec.b) p = { ec.a, ec.b };
		else             p = { ec.b, ec.a };
		ans.push_back(p);
	}
	sort(ans.begin(), ans.end());
	
	fout << cost << endl;
	fout << v-1 << endl;
	for (auto a : ans) {
		fout << a.first << " " << a.second << endl;
	}
	
	return 0;
}

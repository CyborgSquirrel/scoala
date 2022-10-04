#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");

struct Edge {
	int b, v;
};

const int INF = 0x3f3f3f3f;

const int N = 50041;
const int M = 250041;

int n, m;
vector<Edge> gra[N];

int d[N], c[N];
bool inq[N];

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
	
	bool negative_cycle = false;
	queue<int> q;
	d[1] = 0;
	q.push(1);
	inq[1] = true;
	
	while (!negative_cycle && !q.empty()) {
		int a = q.front(); q.pop();
		inq[a] = false;
		for (auto edge : gra[a]) {
			if (d[a] + edge.v < d[edge.b]) {
				d[edge.b] = d[a] + edge.v;
				if (!inq[edge.b]) {
					q.push(edge.b);
					inq[edge.b] = true;
				}
				
				c[edge.b]++;
				if (c[edge.b] >= n) { negative_cycle = true; }
			}
		}
	}
	
	if (negative_cycle) {
		fout << "Ciclu negativ!";
	} else {
		for (int i = 2; i <= n; ++i) {
			fout << d[i] << " ";
		}
	}
	
	return 0;
}

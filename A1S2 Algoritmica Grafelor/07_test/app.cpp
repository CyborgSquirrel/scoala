#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

const int V = 1041;
int v, e;
int src, dst;

int cap[V][V];
int res[V][V];
vector<int> adj[V];

int gen = 0;
int vi[V];
int dp[V], p[V];

int main(int argc, char **argv) {
	fin >> v >> e;
	src = 0; dst = v-1;
	for (int i = 0; i < e; ++i) {
		int a, b, w;
		fin >> a >> b >> w;
		cap[a][b] = w;
		adj[a].push_back(b);
		adj[b].push_back(a);
		if (a == src) {
			dp[a] += w;
		}
	}
	
	auto find_path = []() {
		gen++;
		queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int a = q.front(); q.pop();
			for (auto b : adj[a]) {
				if (vi[b] != gen) {
					int c = min(dp[a], cap[a][b] - res[a][b]);
					if (c > 0) {
						vi[b] = gen;
						dp[b] = c;
						p[b] = a;
						q.push(b);
						if (b == dst) {
							return true;
						}
					}
				}
			}
		}
		return false;
	};
	
	int max_flow = 0;
	while (find_path()) {
		int a = dst;
		int w = dp[dst];
		max_flow += w;
		while (a != src) {
			res[p[a]][a] += w;
			res[a][p[a]] -= w;
			a = p[a];
		}
	}
	
	fout << max_flow;
}

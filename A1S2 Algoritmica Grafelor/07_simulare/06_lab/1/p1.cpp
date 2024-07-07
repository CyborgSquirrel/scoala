#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int V = 1041;
const int E = 50041;

int v, e;
int cap[V][V], res[V][V];
vector<int> adi[V];
int dp[V], pr[V];

int gen = 0;
int vi[V];

int s, t;

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	// ifstream fin("maxflow.in");
	// ofstream fout("maxflow.out");
	
	fin >> v >> e;
	s = 0; t = v-1;
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		fin >> a >> b >> c;
		cap[a][b] = c;
		adi[a].push_back(b);
		adi[b].push_back(a);
		if (a == s) {
			dp[a] += c;
		}
	}
	
	auto find_paths = []() {
		gen++;
		queue<int> q;
		vi[s] = gen;
		q.push(s);
		bool found = false;
		while (!q.empty()) {
			int a = q.front(); q.pop();
			for (auto b : adi[a]) {
				if (vi[b] != gen) {
					dp[b] = min(dp[a], cap[a][b] - res[a][b]);
					if (dp[b] > 0) {
						vi[b] = gen;
						if (b == t) {
							found = true;
						}
						pr[b] = a;
						q.push(b);
					}
				}
			}
		}
		return found;
	};
	
	int max_flow = 0;
	while (find_paths()) {
		for (auto a : adi[t]) {
			int dp_t = min(dp[a], cap[a][t] - res[a][t]);
			if (dp_t > 0) {
				max_flow += dp_t;
				int b = t;
				while (b != s) {
					res[pr[b]][b] += dp_t;
					res[b][pr[b]] -= dp_t;
					b = pr[b];
				}
			}
		}
	}
	
	fout << max_flow;
	
	return 0;
}

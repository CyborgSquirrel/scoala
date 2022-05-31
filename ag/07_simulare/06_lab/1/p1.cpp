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
	
	auto find_path = []() {
		gen++;
		queue<int> q;
		vi[s] = gen;
		q.push(s);
		while (!q.empty()) {
			int a = q.front(); q.pop();
			for (auto b : adi[a]) {
				if (vi[b] != gen) {
					dp[b] = min(dp[a], cap[a][b] - res[a][b]);
					if (dp[b] > 0) {
						vi[b] = gen;
						pr[b] = a;
						if (b == t) {
							return true;
						}
						q.push(b);
					}
				}
			}
		}
		return false;
	};
	
	int max_flow = 0;
	while (find_path()) {
		max_flow += dp[t];
		int a = t;
		while (a != s) {
			res[pr[a]][a] += dp[t];
			res[a][pr[a]] -= dp[t];
			a = pr[a];
		}
	}
	
	fout << max_flow;
	
	return 0;
}

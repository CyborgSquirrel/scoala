#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int V = 1041;
const int E = 50041;

vector<int> gra[V];
int cap[V][V];
int flow[V][V];

int pre[V];
int mflow[V];
int gen[V];

int v, e;

int src, dst;

int maxflow = 0;

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	src = 0;
	dst = v-1;
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		fin >> a >> b >> c;
		cap[a][b] = c;
		gra[a].push_back(b);
		gra[b].push_back(a);
		if (a == src) {
			mflow[a] += c;
		}
	}
	
	int cgen = 0;
	bool found;
	do {
		cgen++;
		found = false;
		
		queue<int> q;
		q.push(src);
		gen[src] = cgen;
		while (!q.empty() && !found) {
			int a = q.front(); q.pop();
			for (int i = 0; i < gra[a].size() && !found; ++i) {
				int b = gra[a][i];
				if (gen[b] != cgen) {
					int c = cap[a][b] - flow[a][b];
					c = min(c, mflow[a]);
					if (c > 0) {
						gen[b] = cgen;
						mflow[b] = c;
						pre[b] = a;
						q.push(b);
						
						if (b == dst) {
							found = true;
						}
					}
				}
			}
		}
		
		if (found) {
			int a = dst;
			int c = mflow[a];
			maxflow += c;
			while (a != src) {
				flow[pre[a]][a] += c;
				flow[a][pre[a]] -= c;
				a = pre[a];
			}
		}
	} while(found);
	
	fout << maxflow;
	
	return 0;
}

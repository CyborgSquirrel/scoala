#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int V = 1041;
const int E = 50041;

int v, e;

int src, dst;
int r[V][V];
int h[V];
int excess[V];
vector<int> gra[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	src = 0;
	dst = v-1;
	h[src] = v;
	
	for (int i = 0; i < e; ++i) {
		int a, b, c;
		fin >> a >> b >> c;
		gra[a].push_back(b);
		gra[b].push_back(a);
		if (a == src) {
			excess[a] -= c;
			excess[b] += c;
			r[b][a] += c;
		} else {
			r[a][b] += c;
		}
	}
	
	int empty = 0;
	int a = 1;
	while (empty < v-2) {
		if (excess[a] == 0) {
			empty++;
		} else {
			empty = 0;
		}
		
		while (excess[a] > 0) {
			for (int i = 0; excess[a] > 0 && i < gra[a].size(); ++i) {
				int b = gra[a][i];
				if (r[a][b] > 0 && h[a] == h[b]+1) {
					// pompare()
						int c = min(excess[a], r[a][b]);
						excess[b] += c;
						excess[a] -= c;
						r[a][b] -= c;
						r[b][a] += c;
					//
				}
			}
			
			// inaltare()
				int mini = -1;
				for (int i = 0; i < gra[a].size(); ++i) {
					int b = gra[a][i];
					if (r[a][b] > 0) {
						if (mini == -1 || h[b] < mini) {
							mini = h[b];
						}
					}
				}
				h[a] = mini+1;
			//
		}
		
		a++;
		if (a >= dst) {
			a = 1;
		}
	}
	
	fout << excess[dst];
	
	return 0;
}

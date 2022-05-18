#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int V = 1041;
const int E = 50041;

int v, e;

int src, dst;
int f[V][V];
int h[V];
int ex[V];
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
			ex[a] -= c;
			ex[b] += c;
			f[b][a] += c;
		} else {
			f[a][b] += c;
		}
	}
	
	int idk = 0;
	int a = 1;
	while (idk < v-2) {
		int old_h = h[a];
		int i = 0;
		while (ex[a] > 0) {
			cout << ex[a] << endl;
			if (i < gra[a].size()) {
				int b = gra[a][i];
				if (f[a][b] > 0 && h[a] == h[b]+1) {
					int c = min(ex[a], f[a][b]);
					
					// pompare()
						ex[b] += c;
						ex[a] -= c;
						f[a][b] -= c;
						f[b][a] += c;
					//
				}
				i++;
			} else {
				// inaltare()
					int mini = -1;
					for (int j = 0; j < gra[a].size(); ++j) {
						int b = gra[a][j];
						if (f[a][b] > 0) {
							if (mini == -1 || h[b] < mini) {
								mini = b;
							}
						}
					}
					h[a] = mini+1;
				//
				i = 0;
			}
		}
		
		if (h[a] <= old_h) {
			idk++;
		} else {
			idk = 0;
		}
		
		a++;
		if (a >= dst) {
			a = 1;
		}
	}
	
	fout << ex[dst];
	
	return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int V = 1041;
const int E = 50041;

int s, t;
int v, e;

int excess[V], h[V];
int res[V][V], cap[V][V];
vector<int> adi[V];

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	s = 0; t = v-1;
	h[s] = v;
	for (int i = 0; i < e; ++i) {
		int a, b, w;
		fin >> a >> b >> w;
		adi[a].push_back(b);
		adi[b].push_back(a);
		cap[a][b] = w;
		if (a == s) {
			res[a][b] += w;
			res[b][a] -= w;
			excess[b] += w;
			excess[a] -= w;
		}
	}
	
	int index = 0;
	vector<int> list;
	for (int i = 1; i < v-1; ++i) {
		list.push_back(i);
	}
	while (index < list.size()) {
		int a = list[index];
		int old_h = h[a];
		while (excess[a] > 0) {
			for (auto b : adi[a]) {
				if (h[a] > h[b]) {
					int c = min(cap[a][b] - res[a][b], excess[a]);
					if (c > 0) {
						res[a][b] += c;
						res[b][a] -= c;
						excess[a] -= c;
						excess[b] += c;
					}
				}
			}
			
			int mini = -1;
			for (auto b : adi[a]) {
				if (cap[a][b] - res[a][b] > 0) {
					if (mini == -1) mini = h[b];
					else mini = min(mini, h[b]);
				}
			}
			if (mini != -1) {
				h[a] = mini+1;
			}
		}
		
		if (h[a] != old_h) {
			list.erase(list.begin()+index);
			list.insert(list.begin(), a);
			index = 0;
		} else {
			index++;
		}
	}
	
	fout << excess[t];
	
	return 0;
}

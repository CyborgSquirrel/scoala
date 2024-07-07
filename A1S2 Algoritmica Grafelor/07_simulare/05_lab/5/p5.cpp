#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int V = 5041;
const int E = 50041;

struct Edge {
	int a, b, w;
};

int v, e;

int tre[V];
int p(int a) {
	if (a != tre[a]) {
		tre[a] = p(tre[a]);
	}
	return tre[a];
}

void merge(int a, int b) {
	a = p(a);
	b = p(b);
	tre[a] = b;
}

bool check(int a, int b) {
	return p(a) == p(b);
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	fin >> v >> e;
	for (int i = 0; i < v; ++i) {
		tre[i] = i;
	}
	
	vector<Edge> ev;
	for (int i = 0; i < e; ++i) {
		Edge e;
		fin >> e.a >> e.b >> e.w;
		ev.push_back(e);
	}
	
	sort(
		ev.begin(), ev.end(),
		[](const Edge &lhs, const Edge &rhs) { return lhs.w < rhs.w; }
	);
	
	int cost = 0;
	vector<Edge> sol;
	for (int i = 0; i < ev.size() && sol.size() < v-1; ++i) {
		auto ec = ev[i];
		if (!check(ec.a, ec.b)) {
			merge(ec.a, ec.b);
			cost += ec.w;
			sol.push_back(ec);
		}
	}
	
	sort(
		sol.begin(), sol.end(),
		[](const Edge &lhs, const Edge &rhs) { return lhs.a < rhs.a || (lhs.a == rhs.a && lhs.b < rhs.b); }
	);
	
	fout << cost << endl;
	fout << sol.size() << endl;
	for (auto ec : sol) {
		fout << ec.a << " " << ec.b << endl;
	}
	
	return 0;
}

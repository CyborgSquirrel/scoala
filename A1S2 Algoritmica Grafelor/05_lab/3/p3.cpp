#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node {
	int lt, rt;
	int v;
	char c;
};

std::string s;
int f[128];
std::string code[128];
Node tre[255];

void make_code(int a, std::string c) {
	Node &node = tre[a];
	if (node.lt == -1 && node.rt == -1) {
		code[(int) node.c] = c;
	} else {
		make_code(node.lt, c+'0');
		make_code(node.rt, c+'1');
	}
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	int n = 0;
	getline(fin, s);
	for (auto c : s) {
		if (f[(int) c] == 0) n++;
		f[(int) c]++;
	}
	
	auto cmp = [](int lhs, int rhs){ return tre[lhs].v > tre[rhs].v || (tre[lhs].v == tre[rhs].v && tre[lhs].c > tre[rhs].c); };
	priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
	
	fout << n << "\n";
	int q = 0;
	for (int c = 0; c < 128; ++c) {
		if (f[c] != 0) {
			 fout << (char) c << " " << f[c] << "\n";
			 
			 Node &node = tre[q];
			 node.c = (char) c;
			 node.lt = node.rt = -1;
			 node.v = f[c];
			 
			 pq.push(q); q++;
		}
	}
	
	while (pq.size() >= 2) {
		auto lt = pq.top(); pq.pop();
		auto rt = pq.top(); pq.pop();
		
		Node &node = tre[q];
		node.v = tre[lt].v + tre[rt].v;
		node.c = min(tre[lt].c, tre[rt].c);
		node.lt = lt;
		node.rt = rt;
		
		pq.push(q); q++;
	}
	
	make_code(q-1, "");
	
	for (auto c : s) {
		fout << code[(int) c];
	}
	
	return 0;
}

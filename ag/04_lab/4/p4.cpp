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
Node tre[255];

char decode(int a, int &i) {
	Node &node = tre[a];
	if (node.lt == -1 && node.rt == -1) {
		return node.c;
	} else {
		char c = s[i];
		i++;
		     if (c == '0') return decode(node.lt, i);
		else if (c == '1') return decode(node.rt, i);
		else return 0; // oh no
	}
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	auto cmp = [](int lhs, int rhs){ return tre[lhs].v > tre[rhs].v || (tre[lhs].v == tre[rhs].v && tre[lhs].c > tre[rhs].c); };
	priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
	
	int n;
	fin >> n;
	int q = 0;
	for (int i = 0; i < n; ++i) {
		 Node &node = tre[q];
		 node.lt = node.rt = -1;
		 fin.get(); fin.get();
		 node.c = fin.get();
		 fin >> node.v;
		 
		 pq.push(q); q++;
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
	
	fin >> s;
	int i = 0;
	while (i < s.size()) fout << decode(q-1, i);
	
	return 0;
}

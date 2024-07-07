#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	Node *lt, *rt;
	char c;
	int f;
	static Node *leaf(char c, int f) {
		return new Node { nullptr, nullptr, c, f };
	}
	static Node *branch(Node *lt, Node *rt) {
		return new Node { lt, rt, min(lt->c, rt->c), lt->f+rt->f };
	}
	~Node() {
		if (lt != nullptr) delete lt;
		if (rt != nullptr) delete rt;
	}
};

int n;
string code;

char decode(Node *node, int &index) {
	if (node->lt == nullptr && node->rt == nullptr) {
		return node->c;
	} else {
		if (code[index] == '0') {
			index++;
			return decode(node->lt, index);
		} else if (code[index] == '1') {
			index++;
			return decode(node->rt, index);
		} else {
			// oh no
			return 0;
		}
	}
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	auto cmp = [](Node *lt, Node *rt) { return !(lt->f < rt->f || (lt->f == rt->f && lt->c < rt->c)); };
	priority_queue<Node*, vector<Node*>, decltype(cmp)> q(cmp);
	
	fin >> n;
	for (int i = 0; i < n; ++i) {
		fin.get(); fin.get(); char c = fin.get();
		int f; fin >> f;
		q.push(Node::leaf(c, f));
	}
	
	while (q.size() >= 2) {
		Node *lt = q.top(); q.pop();
		Node *rt = q.top(); q.pop();
		q.push(Node::branch(lt, rt));
	}
	Node *root = q.top(); q.pop();
	
	fin >> code;
	int index = 0;
	while (index < code.size()) {
		fout << decode(root, index);
	}
	
	return 0;
}

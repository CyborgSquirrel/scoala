#include <iostream>
#include <fstream>
#include <string>
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

int n = 0;
int f[256];
string code[256];
string s;

void generate_code(Node *node, string a="") {
	if (node != nullptr) {
		if (node->lt != nullptr && node->rt != nullptr) {
			generate_code(node->lt, a+"1");
			generate_code(node->rt, a+"0");
		} else {
			code[(int) node->c] = a;
		}
	}
}

int main(int argc, char **argv) {
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	
	getline(fin, s);
	for (auto c : s) {
		if (f[(int) c] == 0) {
			n++;
		}
		f[(int) c]++;
	}
	
	auto cmp = [](const Node *lhs, const Node *rhs) {
		return !(lhs->f < rhs->f || (lhs->f == rhs->f && lhs->c < rhs->c));
	};
	priority_queue<Node*, vector<Node*>, decltype(cmp)> q(cmp);
	
	fout << n << endl;
	for (int i = 0; i < 256; ++i) {
		if (f[i] > 0) {
			q.push(Node::leaf((char) i, f[i]));
			fout << (char) i << " " << f[i] << endl;
		}
	}
	
	while (q.size() >= 2) {
		Node *rt = q.top(); q.pop();
		Node *lt = q.top(); q.pop();
		q.push(Node::branch(lt, rt));
	}
	Node *root = q.top(); q.pop();
	
	generate_code(root);
	for (auto c : s) {
		fout << code[(int) c];
	}
	
	delete root;
	
	return 0;
}

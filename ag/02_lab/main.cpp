#include <iostream>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("graf.txt");

const int N = 41;
const int INF = 0x3F3F3F3F;

int n;
bool t[N][N], g[N][N];

void tranzitiva() {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (!t[i][j]) t[i][j] = t[i][k] && t[k][j];
			}
		}
	}
	
	cout << "=== Matricea inchiderii tranzitive ===\n";
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << t[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void moore() {
	static int m[N], p[N];
	cout << "=== Moore ===\n";
	cout << "start = ";
	int s; cin >> s;
	cout << "end = ";
	int e; cin >> e;
	
	for (int i = 1; i <= n; ++i) m[i] = INF;
	queue<int> q; q.push(s);
	m[s] = 0;
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (int b = 1; b <= n; ++b) {
			if (m[b] == INF && g[a][b]) {
				m[b] = m[a] + 1;
				p[b] = a;
				q.push(b);
			}
		}
	}
	
	stack<int> st;
	int a = e;
	st.push(a);
	while (a != s && a != 0) {
		a = p[a];
		st.push(a);
	}
	
	if (a != 0) {
		cout << "Drumul minim de la " << s << " la " << e << ":\n";
		bool arrow = false;
		while (!st.empty()) {
			if (arrow) cout << " -> ";
			cout << st.top();
			st.pop();
			arrow = true;
		}
		cout << "\n";
	} else {
		cout << "Nu exista drum de la " << s << " la " << e << ".\n";
	}
	cout << "\n";
}

void bfs() {
	static int d[N];
	cout << "=== Bfs ===\n";
	cout << "start = ";
	int s;
	cin >> s;
	
	queue<int> q;
	q.push(s);
	for (int i = 1; i <= n; ++i) d[i] = INF;
	d[s] = 0;
	while (!q.empty()) {
		int a = q.front();
		q.pop();
		for (int b = 1; b <= n; ++b) {
			if (g[a][b] && d[b] == INF) {
				q.push(b);
				d[b] = d[a]+1;
				cout << d[b] << " " << b << "\n";
			}
		}
	}
	cout << "\n";
}

enum COLOR { ALB=0, GRI, NEGRU };
void __dfs_visit(int a) {
	static int time = 0;
	static int d[N], f[N], color[N], p[N];
	
	time++;
	d[a] = time;
	color[a] = GRI;
	for (int b = 1; b <= n; ++b) {
		if (color[b] == ALB && g[a][b]) {
			cout << b << "\n";
			p[b] = a;
			__dfs_visit(b);
		}
	}
	color[a] = NEGRU;
	time++;
	f[a] = time;
}

void dfs_visit() {
	cout << "=== Dfs visit ===\n";
	cout << "start = ";
	int s;
	cin >> s;
	__dfs_visit(s);
	cout << "\n";
}

int main() {
	fin >> n;
	int a, b;
	while (fin >> a >> b) {
		g[a][b] = t[a][b] = true;
	}
	
	tranzitiva();
	moore();
	bfs();
	dfs_visit();
	
	return 0;
}

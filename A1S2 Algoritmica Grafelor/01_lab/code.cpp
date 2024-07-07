#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("./in.txt");

const int N = 41;

struct Muc { int a, b; };

int n;
vector<Muc> muchii;
bool adiac[N][N], inci[N][N];

void read_muchii() {
	Muc m;
	while (fin >> m.a >> m.b) {
		muchii.push_back(m);
	}
}

void make_adiac() {
	for (auto &m : muchii) {
		adiac[m.a][m.b] = adiac[m.b][m.a] = true;
	}
}

void make_inci() {
	int m = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			if (adiac[i][j]) {
				inci[i][m] = inci[j][m] = true;
				m++;
			}
		}
	}
}

void write_adiac() {
	cout << "Matricea de adiacenta:" << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << adiac[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void write_inci() {
	cout << "Matricea de incidenta:" << endl;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < muchii.size(); ++j) {
			cout << inci[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int grad[N];
void make_grad() {
	for (auto &m : muchii) {
		grad[m.a]++;
		grad[m.b]++;
	}
}

void noduri_izolate() {
	bool exista = false;
	for (int i = 1; i <= n; ++i) {
		if (grad[i] == 0) {
			if (!exista) {
				cout << "Noduri izolate:" << endl;
				exista = true;
			}
			cout << i << endl;
		}
	}
	if (!exista) cout << "Nu exista noduri izolate." << endl;
	cout << endl;
}	

void regular() {
	bool este_regular = true;
	int g = grad[1];
	for (int i = 2; i <= n && este_regular; ++i) {
		este_regular &= (grad[i] == g);
	}
	
	if (este_regular) cout << "Graful este regular." << endl;
	else cout << "Graful nu este regular." << endl;
}

const int INF = 0x3F3F3F3F;
int dist[N][N];
void make_dist() {
	for (int a = 1; a <= n; ++a) {
		for (int b = 1; b <= n; ++b) {
			if (adiac[a][b]) {
				dist[a][b] = 1;
			} else if (a == b) {
				dist[a][b] = 0;
			} else {
				dist[a][b] = INF;
			}
		}
	}
	
	for (int c = 1; c <= n; ++c) {
		for (int a = 1; a <= n; ++a) {
			for (int b = 1; b <= n; ++b) {
				dist[a][b] = min(dist[a][b], dist[a][c]+dist[c][b]);
			}
		}
	}
	
	cout << "Matricea distantelor este:" << endl;
	for (int a = 1; a <= n; ++a) {
		for (int b = 1; b <= n; ++b) {
			if (dist[a][b] == INF) {
				cout << "INF" << "\t";
			} else {
				cout << dist[a][b] << "\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool vi[N];
int dfs(int a) {
	int r = 0;
	if (!vi[a]) {
		r++;
		vi[a] = true;
		for (int b = 1; b <= n; ++b) {
			if (!vi[b] && adiac[a][b]) {
				r += dfs(b);
			}
		}
	}
	return r;
}

void conex() {
	if (dfs(1) == n) cout << "Graful este conex.";
	else cout << "Graful nu este conex.";
}

int main(){
	fin >> n;
	
	read_muchii();
	make_adiac();
	make_inci();
	
	write_adiac();
	write_inci();
	
	make_grad();
	noduri_izolate();
	regular();
	make_dist();
	conex();
	
	return 0;
}
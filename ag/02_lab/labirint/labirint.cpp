#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

ifstream fin("labirint_1.txt");

const int N = 1041;
char g[N][N];

struct Vec2 { int x, y; };

Vec2 size {0, 0}, s, e;
void read() {
	Vec2 pos {0, 0};
	for (char c = fin.get(); fin; c = fin.get()) {
		if (c == '\n') {
			pos.y++; pos.x = 0;
		} else {
			if (c == 'S') {
				s.x = pos.x; s.y = pos.y;
			} else if (c == 'F') {
				e.x = pos.x; e.y = pos.y;
			}
			g[pos.x][pos.y] = c;
			pos.x++;
		}
		size.x = max(size.x, pos.x+1);
		size.y = max(size.y, pos.y+1);
	}
}

bool inb(Vec2 v) {
	return v.x >= 0 && v.x < size.x && v.y >= 0 && v.y < size.y;
}

Vec2 p[N][N];
bool vi[N][N];
Vec2 ds[] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
void lee() {
	queue<Vec2> q;
	q.push(s);
	vi[s.x][s.y] = true;
	while (!q.empty() && !vi[e.x][e.y]) {
		Vec2 a = q.front();
		q.pop();
		for (int i = 0; i < 4; ++i) {
			Vec2 d = ds[i];
			Vec2 b = {a.x+d.x, a.y+d.y};
			if (inb(b) && !vi[b.x][b.y] && g[b.x][b.y] != '1') {
				vi[b.x][b.y] = true;
				p[b.x][b.y] = a;
				q.push(b);
			}
		}
	}
}

void trace() {
	Vec2 a = e;
	while ((a.x != 0 || a.y != 0) && (a.x != s.x || a.y != s.y)) {
		a = p[a.x][a.y];
		if (a.x != s.x || a.y != s.y) g[a.x][a.y] = 'x';
	}
}

void write() {
	for (int y = 0; y < size.y; ++y) {
		for (int x = 0; x < size.x; ++x) {
			cout << g[x][y];
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	read();
	lee();
	trace();
	write();
	return 0;
}

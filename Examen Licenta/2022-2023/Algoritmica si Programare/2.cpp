#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 10041;
typedef long long lint;

int n;
lint a[N];
unordered_map<lint, int> m;

struct Answer {
  bool valid;
  int x;
  int y;
  int z;
  int t;
};

Answer solve() {
  lint s = 0;
  for (int x = 0; x < n; ++x) {
    s += a[x];
    for (int y = x+1; y < n; ++y) {
      s += a[y];
      for (int z = y+1; z < n; ++z) {
        s += a[z];

        if (m.count(0-s) != 0) {
          int t = m[0-s];
          if (t != x && t != y && t != z) {
            return {
              true, x, y, z, t,
            };
          }
        }
        
        s -= a[z];
      }
      s -= a[y];
    }
    s -= a[x];
  }

  return {
    false, 0, 0, 0, 0,
  };
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    m[a[i]] = i;
  }

  Answer answer = solve();

  if (answer.valid) {
    cout
      << answer.x << " "
      << answer.y << " "
      << answer.z << " "
      << answer.t << "\n";
  } else {
    cout << "-1\n";
  }
  
  return 0;
}

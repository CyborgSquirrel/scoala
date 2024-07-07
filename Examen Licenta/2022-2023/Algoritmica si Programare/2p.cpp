#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10041;
typedef long long lint;

int n;
lint a[N];

struct Answer {
  bool valid;
  int x;
  int y;
  int z;
  int t;
};

Answer solve() {
  sort(a, a+n);
  for (int x = 0; x < n-3; ++x) {
    for (int y = x+1; y < n-2; ++y) {
      lint target = 0 - (a[x] + a[y]);
      
      int z = y+1;
      int t = n-1;
      while (z < t) {
        lint current = a[z] + a[t];
        if (current < target) {
          z++;
        } else if (current > target) {
          t--;
        } else {
          return {
            true, x, y, z, t,
          };
        }
      }
    }
  }

  return {
    false, 0, 0, 0, 0,
  };
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
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

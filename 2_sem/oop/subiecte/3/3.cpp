// 2 b  (0.5p)
#include <iostream>
#include <vector>
using namespace std;
int main() {
  vector<int> v;
  v.push_back(5);
  v.push_back(7);
  v[0] = 6;
  v.push_back(8);
  auto it = v.begin();
  it = it + 1;
  while (it != v.end()) {
    cout << *it << endl;
    it++;
  }
  return 0;
}

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

int ary[110];
bool cswap[110][110];

int main() {
  ios_base::sync_with_stdio(false);
  int n; cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> ary[i];
  memset(cswap, 0, sizeof cswap);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c; cin >> c;
      if (c == 'Y') cswap[i][j] = cswap[j][i] = true;
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (cswap[i][k] && cswap[k][j])
          cswap[i][j] = cswap[j][i] = true;
      }
    }
  }
  bool swapped;
  do {
    swapped = false;
    for (int i = 0; i < n-1; ++i) {
      for (int j = i+1; j < n; ++j) {
        if ((cswap[i][j] || cswap[j][i]) && ary[i] > ary[j]) {
          swap(ary[i], ary[j]);
          swapped = true;
        }
      }
    }
  } while (swapped);
  for (int i = 0; i < n; ++i) {
    if (i > 0) cout << " ";
    cout << ary[i];
  }
  cout << "\n";
}

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

typedef long long llong;
typedef pair<int, int> int2;
typedef pair<llong, llong> llong2;
#define foreach(v,c) for (typeof((c).begin()) v = (c).begin(); v != (c).end(); ++v)
#define rep(i,n) for (int i = 0; i < (n); ++i)

int n, m;
char s[100][200010], r[100][200010];
int pi[200010];

void kmp(char *str, int len) {
  pi[0] = -1; // pi[0] is undefined
  for(int i = 0; i < len; ++i) {
    int k = pi[i];
    while (k >= 0 && str[k]!=str[i])
    k = pi[k];
    pi[i+1] = k+1;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    s[i][m] = '#';
    for (int j = 0; j < m; ++j) {
      r[i][j] = s[i][m-j-1];
    }
    r[i][m] = '|';
  }
  int best = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      int p = 0;
      while (s[i][p] == r[j][p]) ++p;
      if (p == m) {
        best = max(best, 2*m);
        continue;
      }
      for (int k = m-1, l = m+1; k >= p; --k, ++l) {
        s[i][l] = s[i][k];
        r[j][l] = r[j][k];
      }
      int len = m-p;
      kmp(s[i] + p, len*2+1);
      int x1 = pi[len*2+1];
      kmp(r[j] + p, len*2+1);
      int x2 = pi[len*2+1];
      best = max(best, 2*p + x1);
      best = max(best, 2*p + x2);
    }
  }
  cout << best << endl;
}

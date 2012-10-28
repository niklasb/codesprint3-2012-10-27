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
#define rep(i,n) for (int i = 0; i < (n); ++i)

#define MOD 1000000007

int n, m;
/* last component:
     - 0, if nothing will be counted twice
     - 1, if a spare was rolled last
     - 2, if a strike was rolled last
     - 3, if two strikes were rolled last */
int dp[101][3001][4];

template <typename T, typename U>
inline void add_if(int a, T& x, U y) {
  if (a < 0) return;
  x = (x + y) % MOD;
}

int main() {
  ios_base::sync_with_stdio(false);

  memset(dp, 0, sizeof dp);
  dp[0][0][0] = 1;
  for (int i = 1; i <= 100; ++i) {
    for (int j = 0; j <= 3000; ++j) {
      for (int s = 0; s < 4; ++s) {
        if (s == 0) {
          for (int k = 0; k <= 9; ++k) {
            for (int l = 0; l < 10 - k; ++l) {
              add_if(j-k-l,       dp[i][j][s], dp[i-1][j-k-l][0]);
              add_if(j-k-l-k,     dp[i][j][s], dp[i-1][j-k-l-k][1]);
              add_if(j-k-l-k-l,   dp[i][j][s], dp[i-1][j-k-l-k-l][2]);
              add_if(j-k-l-k-k-l, dp[i][j][s], dp[i-1][j-k-l-k-k-l][3]);
            }
          }
        } else if (s == 1) {
          for (int k = 0; k <= 9; ++k) {
            int l = 10 - k;
            add_if(j-10,       dp[i][j][s], dp[i-1][j-10][0]);
            add_if(j-10-k,     dp[i][j][s], dp[i-1][j-10-k][1]);
            add_if(j-10-k-l,   dp[i][j][s], dp[i-1][j-10-k-l][2]);
            add_if(j-10-k-k-l, dp[i][j][s], dp[i-1][j-10-k-k-l][3]);
          }
        } else if (s == 2) {
          add_if(j-10, dp[i][j][s], dp[i-1][j-10][0]);
          add_if(j-10-10, dp[i][j][s], dp[i-1][j-10-10][1]);
        } else if (s == 3) {
          add_if(j-10-10,    dp[i][j][s], dp[i-1][j-10-10][2]);
          add_if(j-10-10-10, dp[i][j][s], dp[i-1][j-10-10-10][3]);
        }
      }
    }
  }

  int t; cin >> t;
  for (int t_ = 0; t_ < t; ++t_) {
    cin >> n >> m;
    llong res = 0;
    // strike at last (two bonus balls)
    for (int k = 0; k <= 10; ++k) {
      for (int l = 0; l <= ((k == 10) ? 10 : (10 - k)); ++l) {
        add_if(m-k-l,   res, dp[n][m-k-l][2]);
        add_if(m-k-k-l, res, dp[n][m-k-k-l][3]);
      }
    }
    // spare at last (one bonus ball)
    for (int k = 0; k <= 10; ++k)
      add_if(m-k, res, dp[n][m-k][1]);

    // nothing at last
    add_if(m, res, dp[n][m][0]);
    cout << res << endl;
  }
}

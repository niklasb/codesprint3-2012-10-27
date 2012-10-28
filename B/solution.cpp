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

#define NM 2000
#define MM ((NM * NM) / 2)

static vector<int2> adj[NM];
vector<pair<llong, int2> > edges;
set<int> todo;
int n, m, k;

static int path[NM+1];
void init_set(int x) {
  path[x] = x;
}
int find_set(int x) {
  if (path[x] == x) return x;
  return (path[x] = find_set(path[x]));
}
void union_sets(int x, int y) {
  path[find_set(x)] = find_set(y);
}

llong kruskal(int& sets) {
  for (int i = 1; i <= n; i++)
    init_set(i);
  sort(edges.begin(), edges.end());
  llong res = 0;
  size_t xx = edges.size();
  for (int i = 0; i < xx; ++i) {
    if (sets <= k) return res;
    llong w = edges[i].first;
    int a = edges[i].second.first;
    int b = edges[i].second.second;
    if (find_set(a) == find_set(b)) continue;
    res += w;
    union_sets(a, b);
    sets--;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  int T; cin >> T;
  for (int t_ = 0; t_ < T; ++t_) {
    cin >> n >> m >> k;

    todo.clear();
    for (int i = 1; i <= n; ++i) {
      adj[i].clear();
      todo.insert(i);
    }

    for (int i = 0; i < m; ++i) {
      int a, b, w; cin >> a >> b >> w;
      edges.push_back(make_pair(w, make_pair(a, b)));
    }
    int sets = n;
    llong res = kruskal(sets);
    if (sets > k) cout << "Impossible!" << endl;
    else cout << res << endl;
  }
}

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

#define INF 400000000

struct MinCostFlow {
  static const int maxn = 410;
  static const int maxm = 40010;
  typedef int Captype;
  typedef int Valtype;
  static const Captype flowlimit = INF;
  struct edge {
    int node, next; Captype flow; Valtype value;
  } edges[maxm<<1];
  edge *edgem[maxn][maxn];
  int graph[maxn], queue[maxn], pre[maxn], con[maxn], n, m, source, target, top;
  bool inq[maxn];
  Captype maxflow;
  Valtype mincost, dis[maxn];
  MinCostFlow() { memset(graph, -1, sizeof(graph)); top=0;}
  inline int inverse(int x) { return 1 + ((x>>1)<<2)-x; }
  inline void addedge(int u, int v, Captype c, Valtype w) {
    if (c == 0) return;
    //cout << u << " -> " << v << ": " << c << "/" << w << endl;
    edgem[u][v] = &edges[top+1];
    edges[top].value = w; edges[top].flow = c; edges[top].node = v;
    edges[top].next = graph[u]; graph[u] = top++;
    edges[top].value = -w; edges[top].flow = 0; edges[top].node = u;
    edges[top].next = graph[v]; graph[v] = top++;
  }
  bool SPFA() {
    int point, nod, now, head = 0, tail = 1;
    memset(pre, -1, sizeof pre);
    memset(inq, 0, sizeof inq);
    memset(dis, 0x7f, sizeof dis);
    dis[source] = 0; queue[0] = source; pre[source] = source; inq[source] = true;
    while (head != tail) {
      now = queue[head++]; point = graph[now]; inq[now] = false; head %= maxn;
      while (point != -1) {
        nod = edges[point].node;
        if (edges[point].flow > 0 && dis[nod]>dis[now]+edges[point].value) {
          dis[nod] = dis[now] + edges[point].value;
          pre[nod] = now;
          con[nod] = point;
          if (!inq[nod]) {
            inq[nod] = true;
            queue[tail++] = nod;
            tail %= maxn;
          }
        }
        point = edges[point].next;
      }
    }
    return pre[target]!=-1;
  }
  void extend() {
    Captype w = flowlimit;
    for (int u = target; pre[u] != u; u = pre[u])
      w = min(w, edges[con[u]].flow);
    maxflow += w;
    mincost += dis[target]*w;
    for (int u = target; pre[u] != u; u = pre[u]) {
      edges[con[u]].flow -= w;
      edges[inverse(con[u])].flow += w;
    }
  }
  void mincostflow() {
    maxflow = 0; mincost = 0;
    while (SPFA()) extend();
  }
};

#define NM 102
int n, m;
int d[NM][NM];
int l[NM], g[NM];
int gens[NM];

bool cmp(int a, int b) {
  return g[a] + 4*l[a] < g[b] + 4*l[b];
}

int main() {
  //ios_base::sync_with_stdio(false);
  scanf("%d%d", &n, &m);
  fill((int*)d, (int*)d + NM*NM, INF);
  for (int i = 1; i <= NM; ++i) {
    d[i][i] = 0;
    gens[i-1] = i;
  }

  for (int i = 0; i < m; ++i) {
    int a, b, dist;
    scanf("%d%d%d", &a, &b, &dist);
    d[a][b] = d[b][a] = dist;
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &l[i]);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &g[i]);

  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

  sort(gens, gens + n, cmp);

  int ks[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 13, 16, 20, 25, 32, 40, 50, 64, 80, 100};
  MinCostFlow *best = 0;
  llong best_cost = INF;
  int best_gens = -1;
  for (int i = 0; i < sizeof ks / sizeof *ks; ++i) {
    if (ks[i] > n) break;
    llong cost = 0;
    MinCostFlow *f = new MinCostFlow();
    f->source = 1;
    //f->addedge(f->source, 2, 2, 0);
    f->target = 3;
    for (int j = 1; j <= n; ++j) {
      f->addedge(203 + j, f->target, 1, 0);
    }
    for (int j = 0; j < ks[i]; ++j) {
      int gen = gens[j];
      f->addedge(f->source, 4+gen, INF, 0);
      cost += g[gen];
      for (int k = 1; k <= n; ++k)
        if (d[gen][k] < INF)
          f->addedge(4 + gen, 203 + k, 1, d[gen][k]*l[gen]);
    }
    f->mincostflow();
    if (f->maxflow < n) {
      free(f);
      continue;
    }
    //cout << f->maxflow << endl;
    //cout << f->mincost << endl;
    //cout << cost << endl;
    cost += f->mincost;
    //cout << cost << endl;
    if (cost < best_cost) {
      //cout << "cost: " << cost << " i " << i << endl;
      best_cost = cost;
      if (best) free(best);
      best = f;
      best_gens = ks[i];
    } else {
      free(f);
    }
    //break;
  }
  //cout << best_cost << endl;
  cout << best_gens << endl;
  int trans[NM];
  for (int i = 0; i < best_gens; ++i) {
    if (i > 0) cout << " ";
    int gen = gens[i];
    cout << gens[i];
    for (int j = 1; j <= n; ++j) {
      if (best->edgem[4 + gen][203 + j]->flow) trans[j] = gen;
    }
  }
  cout<<endl;
  for (int i = 1; i <= n; ++i) {
    if (i > 1) cout << " ";
    cout << trans[i];
  }
  cout << endl;
}

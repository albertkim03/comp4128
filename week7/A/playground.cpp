
#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <deque>
#include <cstring>
#include <list>
#include <utility>
#include <functional>   

using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;
/*
 *
 * code for network flow
 *
 */

/*
 * graph representation
 */

 struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat;
    vector<vector<int>> adjList;

    FlowNetwork (int _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++) { adjMat[i].resize(n); }
        adjList.resize(n);
    }

    void add_edge (int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }
};

/*
 * ford fulkerson
 */

// add to FlowNetwork struct
bool augment(int u, int t, ll f, vector<bool>& seen) {
  if (u == t) { return true; }
  if (seen[u]) { return false; }
  seen[u] = true;
  for (int v : adjList[u]) {
    if (adjMat[u][v] >= f && augment(v,t,f,seen)) {
      flow_edge(u,v,f);
      return true;
    }
  }
  return false;
}

ll ford_fulkerson(int s, int t) {
  ll res = 0;
  vector<bool> seen(n, false);
  while (augment(s, t, 1, seen)) {
    res++;
    fill(seen.begin(),seen.end(),false);
  }
  return res;
}

/*
 * edmonds karp 1
 */

// add to FlowNetwork struct, replacing Ford-Fulkerson code
ll augment(int s, int t) {
    queue<int> q; // BFS for path with fewest edges
    q.push(s);
    // pred[v] = vertex from which v was found in BFS
    vector<int> pred(n,-1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjList[u]) {
            if (adjMat[u][v] <= 0) { continue; }
            if (pred[v] == -1) {
                pred[v] = u;
                q.push(v);
            }
        }
    }
    if (pred[t] == -1) { return 0; } // can't reach the sink
    ll res = INF; // must be bigger than the largest edge capacity
    // walk over the path backwards to find the minimum edge
    for (int v = t; v != s; v = pred[v]) { res = min(res, adjMat[pred[v]][v]); }
    // do it again to adjust capacities
    for (int v = t; v != s; v = pred[v]) { flow_edge(pred[v],v,res); }
    return res;
}

/*
 * edmonds karp 2
 */

ll edmonds_karp(int s, int t) {
    ll res = 0;
    while (ll x = augment(s,t)) { res += x; }
    return res;
}

/*
 * dinic 1
 */

struct FlowNetwork {
    int n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork (int _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++) { adjMat[i].resize(n); }
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

/*
 * dinic 2
 */

    // constructs the level graph and returns whether the sink is still reachable
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (int v : adjList[u]) {
                if (level[v] == -1 && adjMat[u][v] > 0) { // unseen and has capacity
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[t] != -1;
    }

/*
 * dinic 3
 */

    // finds an augmenting path with up to f flow.
    ll augment(int u, int t, ll f) {
        if (u == t) { return f; } // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            // use only edges in the level graph with remaining capacity
            if (level[v] == level[u] + 1 && adjMat[u][v] > 0) {
                // revised flow is constrained also by this edge
                ll rf = augment(v,t,min(f, adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u,v,rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

/*
 * dinic 4
 */

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s,t)) {
            while (ll x = augment(s, t, INF)) { res += x; }
            // when no further paths, find new level graph
        }
        return res;
    }
};

/*
 * get min cut
 */

void check_reach(int u, vector<bool>& seen) {
  if (seen[u]) { return; }
  seen[u] = true;
  for (int v : adjList[u]) {
    if (adjMat[u][v] > 0) { check_reach(v,seen); }
  }
}

vector<pair<int,int>> min_cut(int s, int t) {
  ll value = dinic(s,t);
  
  vector<bool> seen(n,false);
  check_reach(s,seen);
  
  vector<pair<int,int>> ans;
  for (int u = 0; u < n; u++) {
    if (!seen[u]) { continue; }
    for (int v : adjList[u]) {
        if (!seen[v] && !is_virtual[u][v]) { // need to record this in add_edge()
            ans.emplace_back(u,v);
      }
    }
  }
  return ans;
}

/*
 * project selection
 */

// Construction:
// Nodes 0 to n-1 are the project nodes.
// Nodes n to n+m-1 are the machine nodes.
// Node n+m is the source, n+m+1 is the sink.

int main(void) {
    int n, m, d;
    cin >> n >> m;
    FlowNetwork net(n+m+2);
    int s = n+m, t = n+m+1;
    int totalRevenue = 0;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;
        net.add_edge(s, i, r);
        totalRevenue += r;
    }
    for (int j = 0; j < m; j++) {
        int c;
        cin >> c;
        net.add_edge(n+j, t, c);
    }
    cin >> d;
    for (int k = 0; k < d; k++) {
        int a, b;
        cin >> a >> b;
        net.add_edge(a-1, n+b-1, INF); // INF > all possible outputs.
    }
    cout << totalRevenue - net.dinic(s,t) << '\n';
}

/*
 * magic hours
 */

int main(void) {
    int n, m, k;
    cin >> n >> m >> k;
    int magic = n+m, s = n+m+1, t = n+m+2;
    FlowNetwork net(n+m+3);
    
    for (int j = 0; j < m; j++) {
        int c;
        cin >> c;
        net.add_edge(n+j, t, c); // attractions are nodes n to n+m-1
    }
    vector<int> magicOpen(m);
    for (int j = 0; j < m; j++) { cin >> magicOpen[j]; }
    
    for (int i = 0; i < n; i++) {
        net.add_edge(s, i, 1); // visitors are nodes 0 to n-1
        int b, C, x;
        cin >> b >> C;
        for (int j = 0; j < C; j++) {
            cin >> x;
            x--;
            add_edge(i, n+x, 1);
            if (b && magicOpen[x]) {
                net.add_edge(i, magic, 1);
                b = 0; // avoid repetition, not really necessary
            }
        }
    }
    net.add_edge(magic, t, k);
    cout << net.dinic(s,t) << '\n';
}

/*
 * irrigation
 */

// Construction:
// Nodes 0 to n-1 are the row vertices.
// Nodes n to n+m-1 are the column vertices.
// Node n+m is the source, n+m+1 is the sink.

int n, m;

int main(void) {
    cin >> n >> m;
    int s = n+m, t = n+m+1;
    FlowNetwork net(n+m+2);

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            char ch;
            cin >> ch;
            if (ch == '1') { net.add_edge(r, c+n, 1); }
        }
    }

    for (int r = 0; r < n; r++) { net.add_edge(s, r, 1); }
    for (int c = 0; c < m; c++) { net.add_edge(c+n, t, 1); }

    cout << net.dinic(s,t) << '\n';
}

/*
 * jumping frogs 1
 */

double lo = 0, hi = 1e10;
for (int it = 0; it < 70; it++) {
  double mid = (lo + hi) / 2;
  if (cando(mid)) { hi = mid; }
  else            { lo = mid; }
}
cout << lo << '\n';

/*
 * jumping frogs 2
 */

inline double sqdist(double x1, double y1, double x2, double y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool cando(double X) { // allow jumps of up to X
    if (D < X) { return true; }
    int s = 2*n, t = 2*n+1, tt = 2*n+2; // source, fake sink, real sink
    FlowNetwork net(2*n+3);
    
    for (int i = 0; i < n; i++) {
        int cap = isbig[i] ? INF : 1;
        net.add_edge(2*i, 2*i+1, cap); // in to out
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sqdist(x[i], y[i], x[j], y[j]) < X*X) {
                net.add_edge(2*i+1, 2*j, INF); // out to in
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (x[i] < X)     { net.add_edge(s, 2*i, INF);   }
        if (x[i] + X > D) { net.add_edge(2*i+1, t, INF); }
    }
    
    net.add_edge(t, tt, 2); // limit max flow to 2
    return net.dinic(s,tt) == 2;
}

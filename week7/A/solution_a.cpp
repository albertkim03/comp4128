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

struct pair_hash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1,T2>& p) const noexcept
    {
        // hash the two parts and mix them.
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);

        // use: unordered_map<std::pair<int,int>, int, pair_hash> dist;
        //     visited.insert({0,0});
        //     visited.insert({1,1});
        //     std::pair<int,int> p{0,0};
        //     if (visited.count(p)) std::cout << "(0,0) already visited\n";
        return h1 ^ (h2 << 1);
    }
};

using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

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
                // if (!seen[v] && !is_virtual[u][v]) { // need to record this in add_edge()
                if (!seen[v]) { // need to record this in add_edge()
                        ans.emplace_back(u,v);
                }
            }
        }
        return ans;
    }
};


  

int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int m; cin >> m;
    int c; cin >> c;

    // make grid
    vector<string> grid(m);
    for (int r = 0; r < m; ++r) cin >> grid[r];

    // calculate cost
    vector<long long> cost(26, INF);
    for (int i = 0; i < c; ++i) {
        long long x; cin >> x;
        cost[i] = x;
    }

    auto in  = [&](int r,int col) { 
        return 2*(r*n + col); 
    };

    auto out = [&](int r,int col) { 
        return 2*(r*n + col) + 1; 
    };

    // 0->2mn-1 is all the cells (2 per cell (in and out))
    int S = 2*m*n; // 2mn is source
    int T = S+1; // 2mn + 1 is sink

    // build flow network with enough nodes
    FlowNetwork g(T+1);
    
    // bank row and bank cell index
    int br, bc;

    for (int r = 0; r < m; ++r) for (int c = 0; c < n; ++c) {
        char ch = grid[r][c];
        long long cap;
        if (ch == 'B') { 
            // Bank cell: cannot be barricaded, so infinite capacity
            cap = INF; 
            br=r; bc=c;  // record its position
        }
        else if (ch == '.') { 
            // '.' = not barricadable, so infinite capacity
            cap = INF; 
        }
        else { 
            // Terrain cell: barricading cost taken from cost array
            cap = cost[ch - 'a'];  
        }
        // Connect in->out with this capacity (represents barricade cost)
        g.add_edge(in(r,c), out(r,c), cap);
    }

    // movement direction
    int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1};

    // for each cell
    for (int r = 0; r < m; ++r) for (int col = 0; col < n; ++col) {
        // for each movement
        for (int k = 0; k < 4; ++k){

            int nr=r+dr[k], nc=col+dc[k];
            if (0<=nr && nr<m && 0<=nc && nc<n){
                // Robber can move from current cell out -> neighbor cell in
                // Capacity INF means "cannot be blocked" (movement itself is free)
                g.add_edge(out(r,col), in(nr,nc), INF);
            }

        }
    }

    // for each cell
    for (int r=0;r<m;++r) for (int col=0;col<n;++col) {
        if (r==0 || r==m-1 || col==0 || col==n-1) {
            // Any border cell's out node connects to sink with INF capacity
            g.add_edge(out(r,col), T, INF);
        }
    }
    
    S = out(br, bc);
    
    long long flow = g.dinic(S, T);
    
    cout << (flow >= INF/2 ? -1 : flow) << "\n";
    
    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_a solution_a.cpp
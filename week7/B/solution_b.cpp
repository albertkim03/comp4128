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

    // n = number of heros
    // m = number of monsters
    // k = number of potions
    int n, m, k;
    cin >> n >> m >> k;

    // enough for all hero->monster connection
    // and enough for source->hero and potion->hero
    int S = n + m;
    int T = S + 1;
    int P = T + 1;

    FlowNetwork g(T + 2);

    // build graph
    for (int i = 0; i < n; ++i) {
        int t; cin >> t;

        // add edge for source -> hero
        g.add_edge(S, i, 1);

        // add edge for potion -> hero
        g.add_edge(P, i, 1);


        for (int j = 0; j < t; ++j) {
            int cur_monster; cin >> cur_monster;
            cur_monster = cur_monster - 1;
            // add edge for every hero -> monster
            g.add_edge(i, n + cur_monster - 1, 1);

        }

    }

    // add edge for every monster->sink
    for (int i = 0; i < m; ++i) {
        g.add_edge(n + i - 1, T, 1);
    }

    // add edge from source->potion size k
    g.add_edge(S, P, k);


    long long flow = g.dinic(S, T);

    cout << flow;

    
    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_b solution_b.cpp
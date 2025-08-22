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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // adj list
    vector<vector<pair<int,int>>> adj(n + 1);
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        edges[i] = {a, b};
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    // bridge detect
    vector<int> tin(n + 1, -1), low(n + 1, -1);
    vector<bool> vis(n + 1, false);
    int timer = 0;
    bool hasBridge = false;

    function<void(int,int)> dfs_bridge = [&](int u, int peid) {
        vis[u] = true;
        tin[u] = low[u] = ++timer;
        for (auto [v, id] : adj[u]) {
            if (id == peid) continue;
            if (vis[v]) {
                // back edge
                low[u] = min(low[u], tin[v]);
            } else {
                dfs_bridge(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    // (u,v) is a bridge
                    hasBridge = true;
                }
            }
        }
    };

    //graph is guaranteed connected in the statement, so run once from 1
    dfs_bridge(1, -1);
    if (hasBridge) {
        cout << 0 << '\n';
        return 0;
    }

    // orient edges 
    vector<bool> used(m, false);     
    fill(vis.begin(), vis.end(), false);
    vector<pair<int,int>> dir(m); 

    function<void(int)> dfs_orient = [&](int u) {
        vis[u] = true;
        for (auto [v, id] : adj[u]) {
            if (used[id]) continue;  
            used[id] = true;
            if (!vis[v]) {
                // tree edge: orient u -> v
                dir[id] = {u, v};
                dfs_orient(v);
            } else {
                // back/cross edge: orient u -> v (from current to already-visited)
                dir[id] = {u, v};
            }
        }
    };

    dfs_orient(1);

    for (int i = 0; i < m; ++i) {
        cout << dir[i].first << ' ' << dir[i].second << '\n';
    }
    return 0;
}
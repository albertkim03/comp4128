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
    struct Edge { int v, cap, rev; };
    int N;
    vector<vector<Edge>> G;
    vector<int> level, it;

    FlowNetwork(int n): N(n), G(n), level(n), it(n) {}

    void add_edge(int u, int v, int c) {
        Edge a{v, c, (int)G[v].size()};
        Edge b{u, 0, (int)G[u].size()};
        G[u].push_back(a);
        G[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s] = 0; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : G[u]) if (e.cap > 0 && level[e.v] == -1) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int f) {
        if (!f || u == t) return f;
        for (int &i = it[u]; i < (int)G[u].size(); ++i) {
            auto &e = G[u][i];
            if (e.cap > 0 && level[e.v] == level[u] + 1) {
                int got = dfs(e.v, t, min(f, e.cap));
                if (got) {
                    e.cap -= got;
                    G[e.v][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }

    long long dinic(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (int aug = dfs(s, t, 99999999)) flow += aug;
        }
        return flow;
    }
};


int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_c solution_c.cpp
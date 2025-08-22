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

    // n = number of heros
    // m = number of monsters
    // k = number of potions
    int n; cin >> n;

    vector<vector<char>> grid(n, vector<char>(n, '.'));
    vector<vector<int>> coord_to_flow_pos(n, vector<int>(n, -1));
    int count = 0;

    // read graph
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char cell; cin >> cell;
            grid[i][j] = cell;

            if (cell == '#') {
                coord_to_flow_pos[i][j] = count;
                ++count;
            }
            // // if black connect to source
            // if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
            //     g.add_edge(S, n * i + j, 1);
            // } 
            // // if white connect to sink
            // else {
            //     g.add_edge(n * i + j, T, 1);
            // }
        }
    }

    int S = count + 1;
    int T = S + 1;
    FlowNetwork g(T + 1);

    int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // for each position check black or white then add connection to source or sink
            if (grid[i][j] == '#') {
                // if black connect to source
                if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) {
                    g.add_edge(S, coord_to_flow_pos[i][j], 1);
                }
                
                // if white connect to sink
                else {
                    g.add_edge(coord_to_flow_pos[i][j], T, 1);
                }
            }

            // if black AND oil, check up down left right
            if (((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0)) && grid[i][j] == '#') {
                
                // for each white, check oil
                for (int k = 0; k < 4; ++k){

                    int nr = i + dr[k];
                    int nc = j + dc[k];

                    if (0 <= nr && nr < n && 0 <= nc && nc < n && grid[nr][nc] == '#'){

                        // Robber can move from current cell out -> neighbor cell in
                        // Capacity INF means "cannot be blocked" (movement itself is free)
                        g.add_edge(coord_to_flow_pos[i][j], coord_to_flow_pos[nr][nc], 1);
                    }
                }
            }
        }
    }

    long long flow = g.dinic(S, T);

    cout << flow;

    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_c solution_c.cpp
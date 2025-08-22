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
typedef pair<int, int> edge; // (distance, vertex)

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;

    struct Adj { int w, v; bool rail; };
    vector<vector<Adj>> edges(n + 1); 

    unordered_set<edge, pair_hash> is_rail;
    ll dist[N]; // dist[i] = INF denotes unseen
    vector<long long> minRail(n+1, INF);
    vector<int>       cntRail(n+1, 0);

    // read in roads
    for (int i = 0; i < m; ++i) {
        int u; cin >> u;
        int v; cin >> v;
        int w; cin >> w;

        edges[u].push_back({w, v, false});
        edges[v].push_back({w, u, false});

    }

    // read in rails
    for (int i = 0; i < k; ++i) {
        int v; cin >> v;
        int w; cin >> w;

        edges[1].push_back({w, v, true});
        edges[v].push_back({w, 1, true});

        minRail[v] = min<long long>(minRail[v], w);
        cntRail[v]++;
        is_rail.insert({1, v});
    }

    auto dijkstra = [&](int s) {
        fill(dist, dist+N, INF);
        priority_queue<edge, vector<edge>, greater<edge>> pq;
        pq.emplace(0, s); // distance to s itself is zero
        while (!pq.empty()) {
            // choose (d, v) so that d is minimal
            // i.e. the closest unvisited vertex
            edge cur = pq.top(); pq.pop();
            
            int v = cur.second, d = cur.first;

            if (dist[v] == INF) { // if not seen
                dist[v] = d;
                for (auto nxt : edges[v]) { // relax all edges from v
                    int u = nxt.v, w = nxt.w;
                    if (dist[u] == INF) { pq.emplace(d + w, u); }
                }
            }
        }
    };

    dijkstra(1);

    // find if each node has a road predecessor on some shortest path
    vector<char> hasRoadPred(n+1, 0);
    for (int u = 1; u <= n; ++u) {
        for (const auto& e : edges[u]) {
            if (e.rail) continue;                   // only roads
            if (dist[u] + e.w == dist[e.v]) hasRoadPred[e.v] = 1;
        }
    }

    long long removable = 0;
    for (int v = 2; v <= n; ++v) {
        if (!cntRail[v]) continue;
        if (minRail[v] > dist[v]) {
            removable += cntRail[v];
        } else if (minRail[v] == dist[v]) {
            if (hasRoadPred[v]) removable += cntRail[v];
            else                removable += cntRail[v] - 1; // keep one minimal rail
        }
    }
    cout << removable << '\n';


    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_b solution_b.cpp
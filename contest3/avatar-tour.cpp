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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k; 
    if (!(cin >> n >> m >> k)) return 0;

    int c, d; 
    cin >> c >> d;

    vector<int> h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];

    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];        // 1..k

    // original road graph (bidirectional). We'll keep neighbors in 'edges'.
    vector<vector<edge>> edges(n);
    for (int i = 0; i < m; ++i) {
        int a, b; 
        cin >> a >> b;
        --a; --b;
        edges[a].push_back({0, b});
        edges[b].push_back({0, a});
    }

    // modify edge weight to be positive
    auto turn_to_positive = [&](int v, int u) -> int {
        if (h[v] >= h[u]) return 0;
        return (d - c) * (h[u] - h[v]);
    };

    int FULL = (1<<k) - 1;
    int S = (FULL + 1) * n;

    auto id = [&](int mask, int v) -> int { return mask * n + v; };

    vector<ll> dist(S, INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;

    // start mountain
    for (int v = 0; v < n; ++v) {
        int mask0 = 1 << (p[v] - 1);
        int cur_index = id(mask0, v);

        dist[cur_index] = (-1LL * c * h[v]);
        pq.emplace(dist[cur_index], cur_index);
    }

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        ll dcur = cur.first;
        int state = cur.second;

        if (dcur != dist[state]) {
            continue;
        }

        int mask = state / n;
        int v = state % n;

        for (auto e : edges[v]) {
            int u = e.second;
            int w = turn_to_positive(v, u);
            int nmask = mask | (1 << (p[u] - 1));
            int nid = id(nmask, u);
            ll nd = dcur + w;

            if (nd < dist[nid]) {
                dist[nid] = nd;
                pq.emplace(nd, nid);
            }
        }
    }

    ll ans = INF;
    for (int v = 0; v < n; ++v) {
        int cur_index = id(FULL, v);
        if (dist[cur_index] == INF) continue;

        // undo distance
        ans = min(ans, dist[cur_index] + (1LL * c * h[v]));
    }

    if (ans == INF) {
        cout << "impossible\n";
    } else {
        cout << ans << "\n";
    }
    return 0;
}

//g++-15 -Wall -std=c++17 -o avatar-tour avatar-tour.cpp
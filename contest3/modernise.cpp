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
typedef pair<int,int> ii;


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

    vector<ii> edges[n]; // (weight, destination)
    bool in_tree[n]; fill(in_tree, in_tree + n, false);
    // use 'greater' comparator for min-heap
    priority_queue<ii, vector<ii>, greater<ii>> pq;

    for (int i = 0; i < m; ++i) {
        int a, b, l; 
        cin >> a >> b >> l;
        --a; --b;
        edges[a].push_back({l, b});
        edges[b].push_back({l, a});
    }


    auto prim = [&]() {
        long long total_weight = 0;
        int max_edge = 0;

        pq.emplace(0,0); // start at vertex 0 with total 0
        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();

            int weight = cur.first, v = cur.second;
            // if this vertex was already seen before
            // it must have been seen at a better distance
            if (in_tree[v]) { continue; }

            in_tree[v] = true;
            total_weight += weight;

            max_edge = max(max_edge, weight);

            // add all edges from this vertex
            for (auto nxt : edges[v]) { pq.push(nxt); }
        }
        return total_weight - max_edge;
    };
    
    cout << prim();

    return 0;
}



// g++-15 -Wall -std=c++17 -o modernise modernise.cpp
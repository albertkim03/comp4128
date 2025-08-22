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
struct edge {
    int u, v, w; // u -> v of weight w
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<edge> edges;

    vector<vector<ll>> dist (n, vector<ll>(n));
    vector<vector<ll>> dist1 (n, vector<ll>(n));

    vector<int> steps_taken(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w; cin >> w;

            dist[i][j] = w;
            edges.push_back({i, j, w});
        }
    }

    for (int i = 0; i < n; ++i) {
        int remove; cin >> remove;
        --remove;
        steps_taken[i] = remove;
    }

    reverse(steps_taken.begin(), steps_taken.end());

    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v) { dist[u][v] = INF, dist1[u][v] = INF;}

    // update the distances for every directed edge
    // each edge u -> v with weight w
    for (edge e : edges) { dist[e.u][e.v] = e.w; }

    // every vertex can reach itself
    for (int u = 0; u < n; ++u) { dist[u][u] = 0; }

    // answers
    deque<ll> answers;
    vector<char> used(n, 0);

    for (int temp_i = 0; temp_i < n; ++temp_i) {
        int i = steps_taken[temp_i];
        used[i] = 1;    

        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
                // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
            }
        }
        

        ll sum = 0;

        for (int a = 0; a < n; ++a) {
            if (!used[a]) continue;
            for (int b = 0; b < n; ++b) {
                if (dist[a][b] == INF || !used[b]) continue;

                // cout << "current sum: " << dist[a][b] << "\n";
                sum += dist[a][b];
            }
        }
        answers.push_front(sum);
    }

    while (answers.size()) {
        cout << answers.front() << " "; answers.pop_front();
    }



    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_c solution_c.cpp
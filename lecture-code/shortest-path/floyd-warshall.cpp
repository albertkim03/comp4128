#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>

// #include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (1LL << 61);
// const int INF = (1LL << 30);
// const int INF = 1e9;
const int N = 100010;
int n;
ll dist[N][N];

struct edge
{
    int u, v;
    ll w; // u -> v of weight w
    edge(int _u, int _v, ll _w) : u(_u), v(_v), w(_w) {}
};

vector<edge> edges;

/*
 * floyd warshall
 */

void floydWarshall() {
    // the distance between everything is infinity
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v)
            dist[u][v] = INF;

    // update the distances for every directed edge
    for (edge &e : edges)
        // each edge u -> v with weight w
        dist[e.u][e.v] = e.w;

    // every vertex can reach itself
    for (int u = 0; u < n; ++u)
        dist[u][u] = 0;

    for (int i = 0; i < n; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
                // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);

}

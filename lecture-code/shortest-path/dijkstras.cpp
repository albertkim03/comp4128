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
typedef pair<ll, int> edge; // (distance, vertex)
const int N = 100100;
vector<edge> edges[N];
ll dist[N];
bool seen[N];
priority_queue<edge, vector<edge>, greater<edge>> pq;

// Dijkstras that uses PQ for implicit relaxation
// This requires a SEEN array
void dijkstra (int s) {
  fill(seen,seen+N,false);
  pq.push(edge(0, s)); // distance to s itself is zero
  while (!pq.empty()) {
    // choose (d, v) so that d is minimal
    // i.e. the closest unvisited vertex
    edge cur = pq.top();
    pq.pop();
    int u = cur.second;
    ll d = cur.first;
    if (seen[u]) continue;

    dist[u] = d;
    seen[u] = true;

    // relax all edges from u
    for (edge &nxt : edges[u]) {
      int v = nxt.second;
      ll weight = nxt.first;
      if (!seen[v])
        pq.push(edge(d + weight, v));
    }
  }
}

// Dijkstras with EXPLICIT relaxation - this is needed when we want to count when we want to know how many relaxations there are
// This removes the need of a seen array, and is also different in where we set the distance
void dijkstra2 (int s) {
  fill(dist, dist+N, INF);
  pq.push(edge(0, s)); // distance to s itself is zero
  while (!pq.empty()) {
    
    int u = pq.top().second;
    pq.pop();

    for (edge &e : edges[u]) {
        int v = e.second;
        ll d = e.first;
        if (dist[v] > dist[u] + d) {
            dist[v] = dist[u] + d;
            pq.push({dist[v], v});
        }
    }
  }


}
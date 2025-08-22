typedef pair<int, int> edge; // (distance, vertex)

const int INF = 1000*1000*1000+7; // more than any real distance
const int N = 100100;
vector<edge> edges[N]; // assume prefilled adjlist
int dist[N]; // dist[i] = INF denotes unseen

void dijkstra (int s) {
  fill(dist, dist+N, INF);
  priority_queue<edge, vector<edge>, greater<edge>> pq;
  pq.emplace(0, s); // distance to s itself is zero
  
  while (!pq.empty()) {
    // choose (d, v) so that d is minimal
    // i.e. the closest unvisited vertex
    edge cur = pq.top();
    pq.pop();
    int v = cur.second, d = cur.first;
    if (dist[v] == INF) { // if not seen
      dist[v] = d;
      for (edge nxt : edges[v]) { // relax all edges from v
        int u = nxt.second, w = nxt.first;
        if (dist[u] == INF) { pq.emplace(d + w, u); }
      }
    }
  }
}

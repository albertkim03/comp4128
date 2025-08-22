/*
 * floyd warshall
 */



// the distance between everything is infinity
for (int u = 0; u < n; ++u)
  for (int v = 0; v < n; ++v) { dist[u][v] = INF; }

// update the distances for every directed edge
// each edge u -> v with weight w
for (edge e : edges) { dist[e.u][e.v] = e.w; }

// every vertex can reach itself
for (int u = 0; u < n; ++u) { dist[u][u] = 0; }

for (int i = 0; i < n; i++)
  for (int u = 0; u < n; u++)
    for (int v = 0; v < n; v++) {
      // dist[u][v] is the length of the shortest path from u to v using only 0 to i as intermediate vertices
      // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
      dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
    }

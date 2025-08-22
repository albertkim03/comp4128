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

int n;

const ll N = 100000;
bool scc_seen[N], scc_seen_r[N];
vector<int> edges[N], edges_r[N];
ll postorder[N];
ll p = 0;
int scc[N];

// Alternatively:
// vector<vector<int>> edges(n + 1), edges_r(n + 1);
// vector<bool> scc_seen(n + 1, false), scc_seen_r(n + 1, false);
// vector<int> postorder(n + 1, 0), scc(n + 1, 0);

void initScc(int n) {
    fill(postorder, postorder + N, 0);
    fill(scc, scc + N, 0);
    memset(scc_seen, false, sizeof(scc_seen));
    memset(scc_seen_r, false, sizeof(scc_seen_r));
}

/*
 * kosaraju
 */

void scc_dfs(int u)
{
    if (scc_seen[u])
        return;
    scc_seen[u] = true;
    for (int v : edges[u])
        scc_dfs(v);
    postorder[p++] = u;
}

void scc_dfs_r(int u, int mark)
{
    if (scc_seen_r[u])
        return;
    scc_seen_r[u] = true;
    scc[u] = mark;
    for (int v : edges_r[u])
        scc_dfs_r(v, mark);
}

int compute_sccs()
{
    int sccs = 0;
    for (int i = 1; i <= n; i++)
        if (!scc_seen[i])
            scc_dfs(i);
    for (int i = p - 1; i >= 0; i--)
    {
        int u = postorder[i];
        if (!scc_seen_r[u]) // ignore visited vertices
            scc_dfs_r(u, sccs++);
    }
    return sccs;
}


// Forming a condensation graph after running compute_sccs()
vector<int> condensation_graph[N];
unordered_set<ll> added_edges; // To avoid duplicate edges

// assumes vertices are 1 indexed
void build_condensation_graph(int scc_count)
{
    for (int u = 1; u <= n; u++)
    {
        for (int v : edges[u])
        {
            int scc_u = scc[u];
            int scc_v = scc[v];
            if (scc_u != scc_v)
            {
                // THIS NEEDS TO BE CHANGED
                ll edge_id = 1LL * scc_u * N + scc_v; // Unique ID for the edge
                if (added_edges.find(edge_id) == added_edges.end())
                {
                    added_edges.insert(edge_id);
                    condensation_graph[scc_u].push_back(scc_v);
                }
            }
        }
    }
}

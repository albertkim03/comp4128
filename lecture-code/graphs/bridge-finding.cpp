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

const int N = 100010;

// order of pushing to the DFS stack
// INITIALISED TO -1
int preorder[N];

// counter for preorder sequence
int T = 0;

// reach[u] is the smlalest preorder index of any vertex reachable from u
int reach[N];

// vector of edges
vector<pair<int, int>> bridges;

// edges array
vector<int> edges[N];

void bridge_dfs(int u, int from = -1) {
    preorder[u] = T++;
    reach[u] = preorder[u];

    for (int v : edges[u]) {
        if (v == from) continue;
        if (preorder[v] == -1) {
            // v hasn't been seen before
            bridge_dfs(v,u);
            // if v can't reach anything earlier than itself
            // then u--v is a birdge
            if (reach[v] == preorder[v]) {
                bridges.emplace_back(u,v);
            }
        }
        // anything reachable from v is reachable from u
        reach[u] = min(reach[u], reach[v]);
    }

}
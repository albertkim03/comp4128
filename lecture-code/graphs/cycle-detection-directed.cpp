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

// seen and active arrays, prefixed with "hasCycle" to disambiguate
bool hasCycle_seen[N], hasCycle_active[N];
vector<int> edges[N];

// if active[v] = true, then v is currenly in the recursion stack
// this means if we have an edge to v, and active[v] == true
// then backedge is detected -> cycle

int n;

// verteices that are still marked active when this returns
// are the ones in the cycle detected
bool hasCycle(int u) {
    if (hasCycle_seen[u]) return false;
    hasCycle_active[u] = true;
    hasCycle_seen[u] = true;
    for (int v : edges[u]) {
        if (hasCycle_active[v] || hasCycle(v)) {
            return true;
        }
    }

    hasCycle_active[u] = false;
    return false;
}

// Returns all the vertices that are in the cycle we detected
vector<int> getInCycleVertices() {
    vector<int> inCycle;
    for (int i = 0; i < n; ++i) {
        if (hasCycle_active[i]) inCycle.push_back(i);
    }
    return inCycle;
} 

int main() {
    // run DFS from every unvisited node to detect any cycle
    for (int u = 0; u < n; ++u) {
        if (!hasCycle_seen[u]) {
            if (hasCycle(u)) {
                return false;
            }
        }
    }
    return true;                            // no cycle found
}

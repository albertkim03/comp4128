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

ll parent[N], subtreeSize[N];


// Union-find ds
void init(int n)
{
    for (int i = 0; i < n; ++i)
    {
        parent[i] = i;
        subtreeSize[i] = 1;
    }
}

// with path compression
// amortized O(logn)
int root(int x)
{
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y)
{
    x = root(x);
    y = root(y);

    // if already connected, return
    if (x == y)
        return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtreeSize[x] < subtreeSize[y])
    {
        parent[x] = y;
        subtreeSize[y] += subtreeSize[x];
    }
    else
    {
        parent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }
}

struct edge {
    int u, v;
    ll w;
};

bool operator< (const edge &a, const edge &b) {
    return a.w < b.w;
}

edge edges[N];

int m;

// Returns total weight of the MST
int mst() {
    // sort in increasing size
    sort(edges, edges + m);

    ll totalWeight = 0;
    for (int i = 0; i < m; ++i) {
        edge &e = edges[i];
        // if the endpoints have differnet parents, join them
        // i.e. joining them will not make a cycle
        if (root(e.u) != root(e.v)) {
            join(e.u, e.v);
            totalWeight += e.w;
        }
    }
    return totalWeight;

}




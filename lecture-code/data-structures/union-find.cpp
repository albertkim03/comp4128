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

const ll N = 100010;
ll parent[N], subtreeSize[N];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        subtreeSize[i] = 1;
    }
}

// with path compression
// amortized O(α(n)) - inverse ackernman function, which is <= 5 for any conceivable n
int root(int x) {
   return parent[x] == x ? x : parent[x] = root(parent[x]);
}

// same as above function - expanded for readability
int root(int x) {
    if (parent[x] == x) {
        return x;
    }

    // recursively obtain root
    int rootX = root(parent[x]);
    
    // path compression - attach x directly to root
    parent[x] = rootX;

    return rootX;
}


// amortized O(α(n)) - inverse ackernman function, which is <= 5 for any conceivable n
// join with size heuristic
void join(int x, int y)  {
    x = root(x); y = root(y);

    // if already connected, return
    if (x == y) return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtreeSize[x] < subtreeSize[y]) {
        parent[x] = y;
        subtreeSize[y] += subtreeSize[x];
    } else  {
        parent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }

}


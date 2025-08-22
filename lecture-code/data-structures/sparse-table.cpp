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
const ll LOGN = 18;

// this array stores the original data that we are performing
// range queries on using the sparse table
ll a[N];

// Sparse Table key idea - Precompute the max of all intervals whose lengths are powers of 2
// This can be done in O(nlogn) time since an interval of length 2^k is decomposed into 2^(k-1) intervals
// sparseTable[l][i]  = max a[i ... i + 2^l]
ll sparseTable[LOGN][N];
int log2s[N];

void precomp(int n) {

    // log2s[i] = floor(log_2(i))
    fill(log2s, log2s + N, 0);
    log2s[1] = 0;
    for (int i = 2; i <= n; i++)
        log2s[i] = log2s[i / 2] + 1;

    for (int i = 0; i < n; ++i) {
        //  sparseTable[0][i] = max { a[i... i + 0] } -> itself
        sparseTable[0][i] = a[i];
    }

    for (int l = 1; l < LOGN; ++l) {
        // w = 2^(l-1)
        int w = 1 << (l - 1);
        for (int i = 0; i + 2 * w <= n; ++i) {
            // a[i,i+2w) is made up of a[i,i+w) and a[i+w,i+2w)
            sparseTable[l][i] = max(sparseTable[l-1][i], sparseTable[l - 1][i + w]);
        }
    }
}


// sample query


int main() {
    // Input the initial array
    ll n; cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    precomp(n);

    ll q; cin >> q;
    for (int j = 0; j < q; j++) {
        ll l, r; cin >> l >> r;
        // Problem: Find max of a[l,r)
        int lvl = log2s[r-l];
        cout << max(sparseTable[lvl][l], sparseTable[lvl][r-(1<<lvl)]) << '\n';
    }
}
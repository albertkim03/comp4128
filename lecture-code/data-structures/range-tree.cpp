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

/*  Say we have the vector of data a[n]
    We can imagine every element in a[n] spanned out
    to form the bottom layer of leaf nodes in a range tree
*/

ll n;
ll tree[1 << 19];

// query the sum over [qL, qR), 0-based
// i is the index in the tree, rotted at 1 so children are 2i and 2i + 1
// instead of explicitly storing each node's range of responsibility, [cL, cR), we calculate
// it on the way down.
// the root node is responsbile for [0,n)
ll query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (cL == qL && cR == qR) return tree[i];
    ll mid = (cL + cR) / 2;
    ll ans = 0;
    // query the part withinin the left child [cL, mid) if responsible
    // the range of responsiblity is being updated each time
    // if left, range beocomes [cL, mid)
    if (qL < mid) ans += query(qL, min(qR, mid), i * 2,  cL, mid);
    // if right, range becomes [mid, cR)
    if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

// Range tree update:

/**
 * p = index of array (0-based)
 * v = value that the p-th element will be updated to
 * i = index in the tree, rooted at 1 so children are 2i and 2i + 1
 * similar to the query, instead of explicitly storing each nodes responsibility range
 * we can calculate through each recursion -> updating [cL, cR) everytime we recurse
 */

void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
    if (cR - cL == 1) {
        // this node is a leaf, and have reached where we want to update
        tree[i] = v;
        return;
    }

    // figure out which child of i is responsible for index (p) being updated
    ll mid = (cL + cR) / 2;
    if (p < mid) {
        update(p,v, i*2, cL, mid);
    } else {
        update(p, v, i * 2 + 1, mid, cR);
    }
    // once we have updated the correct child,we can recalculate our stored value
    // CHANGE THIS IF OTHER OPERATIONS ARE NEEDED
    tree[i] = tree[i*2] + tree[i*2 + 1];
}

/*
 * range tree debug
 */

// print the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
void debug(ll i = 1, ll cL = 0, ll cR = n) {
  // print current node's range of responsibility and value
  cerr << "tree[" << cL << "," << cR << ") = " << tree[i];
  
  if (cR - cL > 1) { // not a leaf
    // recurse within each child
    ll mid = (cL + cR) / 2;
    debug(i * 2, cL, mid);
    debug(i * 2 + 1, mid, cR);
  }
}


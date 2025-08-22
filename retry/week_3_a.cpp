#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <tuple>
#include <algorithm>
#include <limits>
#include <bitset>
#include <deque>
#include <cstring>
#include <list>
#include <utility>
#include <functional>   

struct pair_hash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1,T2>& p) const noexcept
    {
        // hash the two parts and mix them.
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);

        // use: unordered_map<std::pair<int,int>, int, pair_hash> dist;
        //     visited.insert({0,0});
        //     visited.insert({1,1});
        //     std::pair<int,int> p{0,0};
        //     if (visited.count(p)) std::cout << "(0,0) already visited\n";
        return h1 ^ (h2 << 1);
    }
};

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

struct Node {
    long long sum;
    long long mx;
    long long lv;
    long long rv;
    bool inc;
    bool dec;
};
Node tree[1 << 19];


Node merge(const Node& a, const Node& b) {
    Node r;
    r.sum = a.sum + b.sum;
    r.mx  = max(a.mx, b.mx);
    r.lv  = a.lv;
    r.rv  = b.rv;
    r.inc = a.inc && b.inc && (a.rv <= b.lv);
    r.dec = a.dec && b.dec && (a.rv >= b.lv);
    return r;
}

// query the sum over [qL, qR), 0-based
// i is the index in the tree, rotted at 1 so children are 2i and 2i + 1
// instead of explicitly storing each node's range of responsibility, [cL, cR), we calculate
// it on the way down.
// the root node is responsbile for [0,n)
Node query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (cL == qL && cR == qR) return tree[i];
    ll mid = (cL + cR) / 2;
    // query the part withinin the left child [cL, mid) if responsible
    // the range of responsiblity is being updated each time
    // if left, range beocomes [cL, mid)
    if (qR <= mid)            // entirely in left child
        return query(qL, qR, i*2, cL, mid);
    if (qL >= mid)            // entirely in right child
        return query(qL, qR, i*2+1, mid, cR);


    // Overlaps both children
    Node left  = query(qL, mid, i * 2, cL, mid);
    Node right = query(mid, qR, i * 2 + 1, mid, cR);
    return merge(left, right);
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
        tree[i] = {v, v, v, v, true, true};
        return;
    }

    // struct Node {
    //     long long sum;
    //     long long mx;
    //     long long lv;
    //     long long rv;
    //     bool inc;
    //     bool dec;
    // };

    // figure out which child of i is responsible for index (p) being updated
    ll mid = (cL + cR) / 2;
    if (p < mid) {
        update(p,v, i*2, cL, mid);
    } else {
        update(p, v, i * 2 + 1, mid, cR);
    }
    // once we have updated the correct child,we can recalculate our stored value
    // CHANGE THIS IF OTHER OPERATIONS ARE NEEDED
    tree[i] = merge(tree[i*2], tree[i*2 + 1]);
}

/*
 * range tree debug
 */

// print the entire tree to stderr
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
// void debug(ll i = 1, ll cL = 0, ll cR = n) {
//   // print current node's range of responsibility and value
//   cerr << "tree[" << cL << "," << cR << ") = " << tree[i];
  
//   if (cR - cL > 1) { // not a leaf
//     // recurse within each child
//     ll mid = (cL + cR) / 2;
//     debug(i * 2, cL, mid);
//     debug(i * 2 + 1, mid, cR);
//   }
// }

int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int m; cin >> m;

    for (int i = 0; i < n; ++i) {
        int difficulty; cin >> difficulty;
        update(i, difficulty);
    }

    for (int i = 0; i < m; ++i) {
        char op;
        int a;
        int b;
        cin >> op >> a >> b;
        a -= 1;
        if (op == 'U') {
            update(a, b);

        } else if (op == 'M') {
            cout << query(a, b).mx << "\n";

        } else if (op == 'S') {
            cout << query(a, b).sum << "\n";

        } else if (op == 'I') {
            cout << query(a, b).inc << "\n";

        } else if (op == 'D') {
            cout << query(a, b).dec << "\n";

        }
    }

    
    return 0;
}



// g++-15 -Wall -std=c++17 -o week_3_a week_3_a.cpp
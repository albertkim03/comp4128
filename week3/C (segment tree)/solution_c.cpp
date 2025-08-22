// g++-15 -Wall -std=c++17 -o solution solution.cpp

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

using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

const int MAXN = (1 << 17);   // 2^17 = 131072
int A[MAXN];                  // input array
int tree[4 * MAXN];           // segment tree


void build(int v, int l, int r, bool op) {
    if (r - l == 1) {
        tree[v] = A[l];
        return;
    }
    int m = (l + r) / 2;
    build(v*2, l, m, op ^ 1);
    build(v*2+1, m, r, op ^ 1);
    if (op)
        tree[v] = tree[v*2] | tree[v*2+1];
    else
        tree[v] = tree[v*2] ^ tree[v*2+1];
}

void update(int v, int l, int r, int pos, int val, bool op) {
    if (r - l == 1) {
        tree[v] = val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m)
        update(v*2, l, m, pos, val, op ^ 1);
    else
        update(v*2+1, m, r, pos, val, op ^ 1);
    if (op)
        tree[v] = tree[v*2] | tree[v*2+1];
    else
        tree[v] = tree[v*2] ^ tree[v*2+1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int N = (1 << n);

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    bool rootOp = (n % 2 == 1);

    build(1, 0, N, rootOp);

    for (int i = 0; i < m; ++i) {
        int p, b;
        cin >> p >> b;
        update(1, 0, N, p-1, b, rootOp);
        cout << tree[1] << "\n";
    }

    return 0;
}


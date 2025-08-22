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

struct Node {
    long long sum;
    long long mx;
    long long lv;
    long long rv;
    bool inc;
    bool dec;
};

ll problems_count;
ll operations_count;
vector<ll> problem_difficulty;
vector<ll> output;

const int MAXN = 100000 + 5;         // a bit of slack
Node problems[4 * MAXN];             // 400 020 slots – always safe

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


 /*
  * range tree update
  */
 
 // p is the index in the array (0-based)
 // v is the value that the p-th element will be updated to
 // i is the index in the tree, rooted at 1 so children are 2i and 2i+1
 // instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
 // the root node is responsible for [0, n)
 void update(int p, int v, int i = 1, int cL = 0, int cR = problems_count) {
    if (cR - cL == 1) {
        // Leaf node: set all fields
        problems[i] = {v, v, v, v, true, true};
        return;
    }

    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);

    // Recompute this node by merging children
    problems[i] = merge(problems[i*2], problems[i*2+1]);
}


// query the sum over [qL, qR) (0-based)
// i is the index in the tree, rooted at 1 so children are 2i and 2i+1
// instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// the root node is responsible for [0, n)
Node query(int qL, int qR, int i = 1, int cL = 0, int cR = problems_count) {
    if (cL == qL && cR == qR)
        return problems[i];

    int mid = (cL + cR) / 2;
    if (qR <= mid)
        return query(qL, qR, i * 2, cL, mid);
    if (qL >= mid)
        return query(qL, qR, i * 2 + 1, mid, cR);

    // Overlaps both children
    Node left  = query(qL, mid, i * 2, cL, mid);
    Node right = query(mid, qR, i * 2 + 1, mid, cR);
    return merge(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> problems_count >> operations_count;

    for (int i = 0; i < problems_count; ++i) {
        ll cur_difficulty;
        cin >> cur_difficulty;

        update(i, cur_difficulty);
    }

    for (int i = 0; i < operations_count; ++i) {
        string instruction;
        ll first;
        ll second;
        Node res;

        cin >> instruction >> first >> second;

        if (instruction == "U") {
            update(first - 1, second);

        } else if (instruction == "M") {
            res = query(first - 1, second);
            output.push_back(res.mx);

        } else if (instruction == "S") {
            res = query(first - 1, second);
            output.push_back(res.sum);

        } else if (instruction == "I") {
            res = query(first - 1, second);
            output.push_back(res.inc ? 1 : 0);

        } else if (instruction == "D") {
            res = query(first - 1, second);
            output.push_back(res.dec ? 1 : 0);
        } 
    }

    for (auto cur : output) {
        cout << cur << "\n";
    }

    return 0;
}

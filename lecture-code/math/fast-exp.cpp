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

// const ll INF = (1LL << 59);
ll INF = (1LL << 30);
// const int INF = 1e9;


// calculates x^n MOD m (Fast exponentation)
// this is O(log n)
ll pow(ll x, ll n, int m) {
    if (n == 0) return 1;
    ll a = pow(x, n / 2, m);
    a = a * a % m;
    if (n % 2 == 1) a = a * x % m;
    return a;
}


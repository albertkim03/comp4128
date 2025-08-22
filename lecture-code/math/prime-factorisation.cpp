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


bool isPrime(ll x) {
    if (x < 2) return false;

    for (ll f = 2; f * f <= x; ++f) {
        if (x % f == 0) {
            return false;
        }
    }

    return true;
}


// Returns prime factors in increasing order with the right multiplicity
vector<ll> factorisePrime(ll x) {

    vector<ll> factors;
    for (ll f = 2; f *f <= x; ++f) {
        while (x % f == 0) {
            factors.push_back(f);
            x /= f;
        }
    }
    if (x != 1) factors.push_back(x);
    return factors;
}

// Sieve of Eratosthenes
// const ll N = 1000000;
// primeFactors[k] contains all the prime factors of number k
vector<vector<ll>> sieve(ll n) {
    vector<vector<ll>> primeFactors(n + 1);
    bool marked[n + 1];
    memset(marked, false, sizeof(marked));

    for (int i = 2; i <= n; ++i) {
        if (marked[i]) continue;
        for (ll j = 2 * i; j <= n; j += i) {
            marked[j] = true;
            ll temp = j;
            while (temp % i == 0)  {
                primeFactors[j].push_back(i);
                temp /= i;
            }
        }
    }
    return primeFactors;
}




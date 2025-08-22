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

int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    ////////// PREPARE POWERS OF 2
    vector<int> powers_of_two;
    unordered_set<int> powers_of_two_exists;
    for (int i = 0; i < 22; ++i) {
        if (i == 0) {
            powers_of_two.push_back(1);
            continue;
        }

        powers_of_two.push_back(powers_of_two[i - 1] * 2);
        powers_of_two_exists.insert(powers_of_two[i]);
    }
    ////////// PREPARE POWERS OF 2


    int n; cin >> n;

    unordered_map<ll, int> factor_to_occurence;

    auto primeFactors = factorisePrime(n);

    for (const auto & factor : primeFactors) {
        factor_to_occurence[factor] += 1;
    }

    // count max factor multiplicity
    int max_multiplicity = 0;
    for (auto & [a, b] : factor_to_occurence) {
        max_multiplicity = max(max_multiplicity, b);
    }

    // early exit
    if (max_multiplicity <= 1) {
        cout << n << " " << 0;
        return 0;
    }

    // otherwise
    ll full_number = 1;

    int T = 0;
    while ((1 << T) < max_multiplicity) T++;
    int P = 1 << T; // P = 2^T
    bool needs_multiple = false;
    int seen_multiple = 0;

    for (auto & [a, b] : factor_to_occurence) {
        if (powers_of_two_exists.count(b) == 0) {
            needs_multiple = true;
        } else {
            for (int i = 0; i < 22; ++i) {
                if (powers_of_two[i] - max_multiplicity >= 0) {
                    seen_multiple = i;
                    break;
                }
            }
        }
        break;
    }

    for (auto & [a, b] : factor_to_occurence) {
        // calculate the full numbers
        full_number = full_number * a;

        // if (powers_of_two_exists.count(b) == 0) {
        //     needs_multiple = true;
        // }

        if (powers_of_two[seen_multiple] != b) {
            needs_multiple = true;
        }
        // if (b % P != 0) {
        //     needs_multiple = true;
        // }
    }


    ll operations;

    for (int i = 0; i < 22; ++i) {
        if (powers_of_two[i] - max_multiplicity >= 0) {
            operations = needs_multiple ? i + 1 : i;
            break;
        }
    }


    cout << full_number << " " << operations;


    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_b solution_b.cpp
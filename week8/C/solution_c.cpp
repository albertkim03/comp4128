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
const ll MOD = 1000 * 1000 * 1000 + 7;
// const int N =1e5+10;

/*
 * matrix mult
 */

// Implementation for square matrices.
struct Matrix {
    int n;
    vector<vector<ll>> v;
  
    Matrix(int _n) : n(_n) {
      v.resize(n);
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          v[i].push_back(0);
    }
  
    // Matrix operator*(const Matrix &o) const {
    //   Matrix res(n);
    //   for (int i = 0; i < n; i++)
    //     for (int j = 0; j < n; j++)
    //       for (int k = 0; k < n; k++)
    //         // ADD MOD HERE IF NEEDED
    //         res.v[i][j] += v[i][k] * o.v[k][j];
    //       // e.g.
    //       // res.v[i][j] % MOD;
    //       // res.v[i][j] = res.v[i][j] % MOD + (((v[i][k] % MOD) * (o.v[k][j] % MOD)) % MOD);
    //       // res.v[i][j] % MOD;
    //   return res;
    // }
    Matrix operator*(const Matrix &o) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
          for (int k = 0; k < n; ++k) if (v[i][k]) {
            long long aik = v[i][k];
            for (int j = 0; j < n; ++j) if (o.v[k][j]) {
              res.v[i][j] += aik * o.v[k][j];
              if (res.v[i][j] >= (1LL<<62)) res.v[i][j] %= MOD; // optional safety
              if (res.v[i][j] >= MOD) res.v[i][j] %= MOD;
            }
          }
        }
        // final pass to ensure all < MOD
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) res.v[i][j] %= MOD;
        return res;
      }
  
    static Matrix getIdentity(int n) {
      Matrix res(n);
      for (int i = 0; i < n; i++)
        res.v[i][i] = 1;
      return res;
    }
    
    Matrix operator^(ll k) const {
      Matrix res = Matrix::getIdentity(n);
      Matrix a = *this;
      while (k) { // building up in powers of two
        if (k&1) res = res*a;
        a = a*a;
        k /= 2;
      }
      return res;
    }
};
  
static vector<ll> matvec(const Matrix& A, const vector<ll>& x) {
    int n = A.n;
    vector<ll> r(n, 0);
    for (int i = 0; i < n; ++i) {
        long long s = 0;
        for (int j = 0; j < n; ++j) if (A.v[i][j]) {
            s += A.v[i][j] * x[j] % MOD;
            if (s >= (1LL<<62)) s %= MOD;
        }
        r[i] = s % MOD;
    }
    return r;
}
  
  
int main() {
    long long N; int M;
    cin >> N >> M;
    // total configurations = M^N

    // dp(n) = dp(n-1) + dp(n-M), dp(0)=1, dp(n<0)=0
    if (N == 0) { cout << 1 << '\n'; return 0; }
    if (N < M)   { cout << 1 << '\n'; return 0; } // only all-1’s fit

    // Build companion matrix T (size M)
    Matrix T(M);
    T.v[0][0]   = 1;        // dp(n-1)
    T.v[0][M-1] = 1;        // dp(n-M)
    for (int i = 1; i < M; ++i) T.v[i][i-1] = 1; // shift

    // Base state for n = M-1 : [dp(M-1), dp(M-2), ..., dp(0)] = all 1’s
    vector<ll> base(M, 1);

    long long exp = N - (M - 1);
    Matrix P = T ^ exp;
    vector<ll> stateN = matvec(P, base);

    cout << stateN[0] % MOD << '\n';  // dp(N)
    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_c solution_c.cpp
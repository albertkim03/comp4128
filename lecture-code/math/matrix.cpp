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

  Matrix operator*(const Matrix &o) const {
    Matrix res(n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        for (int k = 0; k < n; k++)
          // ADD MOD HERE IF NEEDED
          res.v[i][j] += v[i][k] * o.v[k][j];
        // e.g.
        // res.v[i][j] % MOD;
        // res.v[i][j] = res.v[i][j] % MOD + (((v[i][k] % MOD) * (o.v[k][j] % MOD)) % MOD);
        // res.v[i][j] % MOD;
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






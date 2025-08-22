/*
 *
 * code for math
 *
 */

/*
 * primes
 */

 #include <vector>
 using namespace std;
 
 bool isprime(int x) {
   if (x < 2) return false;
 
   for (int f = 2; f*f <= x; f++) {
     if (x % f == 0) { return false; }
   }
   
   return true;
 }
 
 // Returns prime factors in increasing order with right multiplicity.
 vector<int> primefactorize(int x) {
   vector<int> factors;
   for (int f = 2; f*f <= x; f++)
     while (x % f == 0) {
       factors.push_back(f);
       x /= f;
     }
 
   if (x != 1) { factors.push_back(x); }
   return factors;
 }
 
 /*
  * sieve
  */
 
 int lp[N+1]; // least prime factor
 
 void sieve (void) {
   for (int i = 2; i <= N; i++) { lp[i] = i; }
   for (int i = 2; i*i <= N; i++) {
     if (lp[i] == i) { // prime
       for (int j = i*i; j <= N; j += i) {
         // first prime factor is also smallest
         if (lp[j] == j) { lp[j] = i; }
       }
     }
   }
 }
 
 vector<int> factorisation (int x) {
   vector<int> ret;
   while (x > 1) {
     ret.push_back(lp[x]);
     x /= lp[x];
   }
   return ret;
 }
 
 /*
  * goldbach
  */
 
 #include <iostream>
 using namespace std;
 
 const int N = 1001001;
 int primes[N], P;
 bool notprime[N];
 
 int main() {
   // sieve
   notprime[0] = notprime[1] = true;
   for (int i = 2; i < N; i++) {
     if (notprime[i]) { continue; }
     // if i is prime, mark all its multiples as not prime
     primes[P++] = i;
     for (int j = i*i; j < N; j += i) { notprime[j] = true; }
   }
 
   int n;
   cin >> n;
   // scan primes[] for pair adding to n
   for (int i = 1; i < P; i++) { // primes[0] = 2, skip
     int p = primes[i], q = n-p;
     if (!notprime[q]) {
       cout << n << " = " << p << " + " << q << '\n';
       break;
     }
   }
 }
 
 /*
  * gcd
  */
 
 int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
 
 /*
  * gcd extended
  */
 
 int gcd(int a, int b, int& x, int& y) {
   if (a == 0) {
     x = 0; y = 1;
     return b;
   }
   int x1, y1;
   int d = gcd(b % a, a, x1, y1);
   x = y1 - (b / a) * x1;
   y = x1;
   return d;
 }
 
 /*
  * matrix mult
  */
 
 // Implementation for square matrices.
 struct Matrix {
   int n;
   vector<vector<long long>> v;
 
   Matrix(int _n) : n(_n) {
     v.resize(n);
     for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
         v[i].push_back(0);
       }
     }
   }
 
   Matrix operator*(const Matrix &o) const {
     Matrix res(n);
     for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
         for (int k = 0; k < n; k++) {
           res.v[i][j] += v[i][k] * o.v[k][j];
         }
       }
     }
     return res;
   }
 };
 
 /*
  * matrix exp
  */
 
 // Implementation for square matrices.
 struct Matrix {
   int n;
   vector<vector<long long>> v;
   // Assume these have been implemented.
   Matrix(int _n);
   Matrix operator*(const Matrix &o) const;
 
   static Matrix getIdentity(int n) {
     Matrix res(n);
     for (int i = 0; i < n; i++) { res.v[i][i] = 1; }
     return res;
   }
   
   Matrix operator^(long long k) const {
     Matrix res = Matrix::getIdentity(n);
     Matrix a = *this;
     while (k) { // building up in powers of two
       if (k&1) { res = res*a; }
       a = a*a;
       k /= 2;
     }
     return res;
   }
 };
 
 /*
  * freddy frog
  */
 
 const long long MOD = 1000*1000*1000+7;
 const int MAXJUMP = 100;
 
 struct Matrix {
   Matrix(int _n);
   Matrix operator*(const Matrix &o) const; // modulo MOD throughout
   static Matrix getIdentity(int n);
   Matrix operator^(long long k) const;
 };
 
 int main() {
   int n, k;
   cin >> n >> k;
   Matrix rec(MAXJUMP);
   for (int i = 0; i < k; i++) {
     int d;
     cin >> d;
     rec.v[0][d-1] = 1; // top row of transition matrix
   }
   
   // other rows of transition matrix
   for (int i = 1; i < MAXJUMP; i++) { rec.v[i][i-1] = 1; }
   
   rec = rec^n;
   // (w_n, w_{n-1},...,w_{n-99}) is n steps forward
   // from (w_0,w_{-1},w_{-2},...,w_{-99})
   //    = (1,0,0,...,0)
   cout << rec.v[0][0] << '\n';
 }
 
 /*
  * combinations
  */
 
 typedef long long ll;
 
 const int N = 1001001;
 ll f[N];
 ll modpow(ll a, ll b, int c); // as earlier, but modulo c
 
 ll inv(ll x) {
   return modpow(x, MOD-2, MOD); // Fermat's little theorem
 }
 
 int main() {
   // factorials
   f[0] = 1;
   for (int i = 1; i < N; i++) { f[i] = (i * f[i-1]) % MOD; }
 
   int T;
   cin >> T;
   for (int i = 0; i < T; i++) {
     int n, k;
     cin >> n >> k;
     ll res = (f[n] * inv(f[n-k])) % MOD;
     res = (res * inv(f[k])) % MOD;
     cout << res << '\n';
   }
 }
 
 /*
  * path length on tree subtree only
  */
 
 const int N = 100100;
 vector<int> children[N]; // assume prepopulated, with root 0
 int subtreeSize[N]; // size of each subtree
 long long sumOfDepths[N]; // sum of depths of each subtree
 
 void calcSubtreeSums(int c = 0) {
     subtreeSize[c] = 1;
     for (int ch : children[c]) {
         calcSubtreeSums(ch);
         subtreeSize[c] += subtreeSize[ch];
         // Each depth in ch's subtree increases by 1
         // when we move from ch to c.
         sumOfDepths[c] += subtreeSize[ch] + sumOfDepths[ch];
     }
 }
 
 /*
  * path length on tree lca solution
  */
 
 const int N = 100100;
 vector<int> children[N]; // assume prepopulated, with root 0
 int subtreeSize[N]; // size of each subtree
 long long sumOfDepths[N]; // sum of depths of each subtree
 
 // counts unordered pairs, so double the answer
 long long sumOfPathLengths(int l = 0) {
     long long sumPaths = 0;
     for (int ch : children[l]) { sumPaths += sumOfPathLengths(ch); }
     }
     // 1 to make sure we count paths starting at l.
     long long numNodesSeen = 1;
     long long sumDepthsSoFar = 0;
     for (int ch : children[l]) {
         // consider all paths from nodes seen to nodes in this subtree.
         sumPaths += sumDepthsSoFar * subtreeSize[ch];
         // again, we add subtreeSize[ch] since we need sum of depths relative to l, not ch
         sumPaths += numNodesSeen * (sumOfDepths[ch] + subtreeSize[ch]);
         sumDepthsSoFar += sumOfDepths[ch] + subtreeSize[ch];
         numNodesSeen += subtreeSize[ch];
     }
     return sumPaths;
 }
 
 /*
  * path length on tree sum over edges
  */
 
 const int N = 100100;
 vector<int> children[N]; // assume prepopulated, with root 0
 int subtreeSize[N]; // size of each subtree
 
 int n;
 
 // counts unordered pairs, so double the answer
 long long sumOfPathLengths(int c = 0) {
     long long sumPaths = 0;
     for (int ch : children[c]) {
         sumPaths += sumOfPathLengths(ch);
         sumPaths += (n - subtreeSize[ch]) * subtreeSize[ch];
     }
     return sumPaths;
 }
 
 /*
  * diverse committee 1
  */
 
 #include <bits/stdc++.h>
 using namespace std;
 
 const long long MOD = 1000000007;
 const int N = 220, K = 550;
 long long binom[N][N];
 
 long long madd(long long a, long long b) {
     return (a + b) % MOD;
 }
 
 void precomp() {
     for (int i = 0; i < N; i++) {
         binom[i][0] = 1;
         for (int j = 1; j <= i; j++) {
             binom[i][j] = madd(binom[i-1][j-1], binom[i-1][j]);
         }
     }
 }
 
 /*
  * diverse committee 2
  */
 
 int l[K], u[K];
 long long dp[K][N];
 
 int main() {
     precomp();
 
     int n, k;
     cin >> n >> k;
 
     // 1-indexing is nicer as now our base case corresponds to r = 0.
     for (int r = 1; r <= k; r++) { cin >> l[r] >> u[r]; }
 
     // Base case:
     dp[0][0] = 1;
     for (int r = 1; r <= k; r++) {
         for (int t = 0; t <= n; t++) {
             // Careful: there are no subsets of {1,..,n} with size s > t.
             for (int s = l[r]; s <= min(u[r], t); s++) {
                 dp[r][t] = madd(dp[r][t], binom[t][s]*dp[r-1][t-s]);
             }
         }
     }
     cout << dp[k][n] << '\n';
 }
 
 /*
  * careless secretary slow
  */
 
 #include <bit>
 #include <iostream>
 using namespace std;
 
 typedef long long ll;
 
 const ll MOD = 1000*1000*1000+7;
 const int N = 100100;
 ll fact[N];
 
 inline ll madd(ll a, ll b) { return ((a + b) % MOD + MOD) % MOD; }
 
 int main() {
     fact[0] = 1;
     for (int i = 1; i < N; i++) { fact[i] = (i * fact[i-1]) % MOD; }
 
     int n, k;
     cin >> n >> k;
     ll ans = 0;
     for (int i = 0; i < (1 << k); i++) {
         int bitcount = popcount(i); // __builtin_popcount() before C++20
         int sign = (bitcount % 2) ? -1 : 1;
         ans = madd(ans, sign * fact[n-bitcount]);
     }
     cout << ans << '\n';
 }
 
 /*
  * careless secretary
  */
 
 inline ll madd(ll a, ll b) { return ((a + b) % MOD + MOD) % MOD; }
 inline ll mmult(ll a, ll b) { return (a*b) % MOD; }
 // Add your modinv (and probably your modpow) code here
 ll modinv(ll x);
 
 ll fact[N], invfact[N];
 
 ll choose(ll n, ll r) {
     return mmult(fact[n], mmult(invfact[r], invfact[n-r]));
 }
 
 int main() {
     fact[0] = invfact[0] = 1;
     for (int i = 1; i < N; i++) {
         fact[i] = (i * fact[i-1]) % MOD;
         invfact[i] = modinv(fact[i]);
     }
 
     int n, k;
     cin >> n >> k;
     ll ans = 0;
     for (int i = 0; i <= k; i++) {
         int sign = i % 2 ? -1 : 1;
         // (-1)^i * (K choose i) * (N-i)!
         ll cways = mmult(choose(k, i), fact[n-i]);
         ans = madd(ans, sign * cways);
     }
     cout << ans << '\n';
 }
 
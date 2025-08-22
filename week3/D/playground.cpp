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

using namespace std;
typedef long long ll;

/*
 * range tree query
 */

//  const int N = 100100;
 // the number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
 int tree[1<<18];
 
 int n; // actual length of underlying array
 
 // query the sum over [qL, qR) (0-based)
 // i is the index in the tree, rooted at 1 so children are 2i and 2i+1
 // instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
 // the root node is responsible for [0, n)
 int query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
   // the query range exactly matches this node's range of responsibility
   if (cL == qL && cR == qR)
     return tree[i];
   // we might need to query one or both of the children
   int mid = (cL + cR) / 2;
   int ans = 0;
   // query the part within the left child [cL, mid), if any
   if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cL, mid);
   // query the part within the right child [mid, cR), if any
   if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
   return ans;
 }
 
 /*
  * range tree update
  */
 
 // p is the index in the array (0-based)
 // v is the value that the p-th element will be updated to
 // i is the index in the tree, rooted at 1 so children are 2i and 2i+1
 // instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
 // the root node is responsible for [0, n)
 void update(int p, int v, int i = 1, int cL = 0, int cR = n) {
   if (cR - cL == 1) {
     // this node is a leaf, so apply the update
     tree[i] = v;
     return;
   }
   // figure out which child is responsible for the index (p) being updated
   int mid = (cL + cR) / 2;
   if (p < mid)
     update(p, v, i * 2, cL, mid);
   else
     update(p, v, i * 2 + 1, mid, cR);
   // once we have updated the correct child, recalculate our stored value.
   tree[i] = tree[i*2] + tree[i*2+1];
 }





 const int N = 8;
 const int LOGN = 4;
 int a[N] = {1, 2, 3, 4, 5, 6, 7, 8};
 // sparseTable[l][i] = max a[i..i+2^l)
 int sparseTable[LOGN][N];
 
 void precomp(int n) {
     // Level 0 is the array itself
     for (int i = 0; i < n; i++)
         sparseTable[0][i] = a[i];
 
     // Build higher levels
     for (int l = 1; l < LOGN; l++) {
         int w = 1 << (l - 1); // 2^(l-1)
         for (int i = 0; i + 2 * w <= n; i++)
             sparseTable[l][i] = max(sparseTable[l - 1][i], sparseTable[l - 1][i + w]);
     }
 
     // Print each level
     for (int l = 0; l < LOGN; l++) {
         cout << "Level " << l << ": ";
         int limit = n - (1 << l) + 1;
         for (int i = 0; i < limit; i++) {
             cout << sparseTable[l][i] << " ";
         }
         cout << endl;
     }
 }
 
 int main() {
     precomp(N);
     return 0;
 }

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

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;

    vector<int> initial_trees(n, 0);
    vector<vector<int>> cost (n, vector<int>(m + 1, 0));

    // initialise given trees
    for (int i = 0; i < n; ++i) {
        int cur_tree; cin >> cur_tree;

        initial_trees[i] = cur_tree;
    }

    // initialise given cost
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cur_cost; cin >> cur_cost;

            cost[i][j] = cur_cost;
        }
    } 

    vector<vector<ll>> cur(k+1, vector<ll>(m+1, INF));  // dp[i][g][c]
    vector<vector<ll>> nxt(k+1, vector<ll>(m+1, INF));  // dp[i+1][g][c]
    cur[0][0] = 0;  

    // for each tree
    for (int i = 0; i < n; ++i) {
        fill(nxt.begin(), nxt.end(), vector<ll>(m + 1, INF));

        // for each grouping
        for (int g = 0; g <= k; ++g) {

            // for each last-used colour
            for (int last = 0; last <= m; ++last) {
                if (cur[g][last] == INF) continue;
                
                // means we can't paint new
                if (initial_trees[i] != 0) {
                    int col = initial_trees[i];
                    int ng = (col != last) ? g + 1 : g;
                    
                    // if the new grouping is within the range
                    // take into 
                    if (ng <= k) {
                        nxt[ng][col] = min(nxt[ng][col], cur[g][last]);
                    }
                    
                } 

                // we can paint new
                else {
                    // for each new coloru combination
                    for (int col = 1; col <= m; ++col) {
                        int ng = (col != last) ? g + 1 : g;
                        
                        // too many groups
                        if (ng > k) continue;

                        nxt[ng][col] = min(nxt[ng][col], cur[g][last] + cost[i][col]);

                    }
                }
            }
        }

        cur.swap(nxt);
    }


    ll min_cost = INF;

    for (auto value : cur[k]) {
        
        min_cost = min(min_cost, value);
    }
    (min_cost == INF) ? cout << -1 :  cout << min_cost;
    
    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_c solution_c.cpp
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

    ll total = 0;

    int players[2][n];

    vector<vector<int>> dp(2, vector<int>(n, 0));

    // row 1 of players
    for (int i = 0; i < n; ++i) {
        int cur_player; cin >> cur_player;

        players[0][i] = cur_player;
    }
    
    // row 2 of players
    for (int i = 0; i < n; ++i) {
        int cur_player; cin >> cur_player;

        players[1][i] = cur_player;
    }

    // dp for the best solution
    ll best_0 = players[0][0];
    ll best_1 = players[1][0];

    for (int i = 1; i < n; ++i) {
        dp[0][i] = best_1 + players[0][i];
        dp[1][i] = best_0 + players[1][i];

        best_0 = max(best_0, (ll)dp[0][i]);
        best_1 = max(best_1, (ll)dp[1][i]);

    }


    cout << max(best_0, best_1);

    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_a solution_a.cpp
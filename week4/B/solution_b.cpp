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
const ll N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    ll m; cin >> m;
    ll k; cin >> k;

    vector<ll> ith_satisfaction(n);
    vector<vector<ll>> bonus(n, vector<ll>(n, 0));

    for (ll i = 0; i < n; ++i) {
        ll cur_satisfaction; cin >> cur_satisfaction;
        ith_satisfaction[i] = cur_satisfaction;
    }

    for (ll i = 0; i < k; ++i) {
        ll first; cin >> first;
        first -= 1;
        ll second; cin >> second;
        second -=1;
        ll score; cin >> score;

        bonus[first][second] = score;
    }

    ll MAX_MASK = 1LL << n; // 2^n
    vector<vector<ll>> dp(MAX_MASK, vector<ll>(n, 0));

    // Picking just one dish as a starting poll
    for (ll i = 0; i < n; ++i) {
        dp[1 << i][i] = ith_satisfaction[i];
    }

    for (ll mask = 0; mask < MAX_MASK; ++mask) {
        for (ll last = 0; last < n; ++last) {
            if (!(mask & (1 << last))) continue;  // last must be part of the mask
    
            for (ll next = 0; next < n; ++next) {
                if (mask & (1 << next)) continue; // already picked
    
                ll new_mask = mask | (1 << next);
                ll bonus_score = bonus[last][next];
    
                dp[new_mask][next] = (ll)max(
                    dp[new_mask][next],
                    dp[mask][last] + ith_satisfaction[next] + bonus_score
                );
            }
        }
    }

    //answer
    ll ans = 0;
    for (ll mask = 0; mask < MAX_MASK; ++mask) {
        if (__builtin_popcount(mask) != m) continue;

        for (ll last = 0; last < n; ++last) {
            ans = max(ans, dp[mask][last]);
        }
    }
    cout << ans;
        




    
    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_b solution_b.cpp
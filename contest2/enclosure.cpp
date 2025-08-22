// g++-15 -Wall -std=c++17 -o solution solution.cpp

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


using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;
const int MAX_N = 62;

ll prefix_sum[MAX_N][MAX_N];
short dp[MAX_N][MAX_N][MAX_N][MAX_N];
ll T;

// O(1) rectangle sum query
ll rect_sum(int r1, int c1, int r2, int c2) {
    return prefix_sum[r2][c2] - prefix_sum[r1-1][c2] - prefix_sum[r2][c1-1] + prefix_sum[r1-1][c1-1];
}

// Recursive DP function
int solve(int r1, int c1, int r2, int c2) {
    short &memo = dp[r1][c1][r2][c2];
    if (memo != -1) return memo;

    if (rect_sum(r1, c1, r2, c2) <= T)
        return memo = 0;

    if (r1 == r2 && c1 == c2)
        return memo = 30000; // impossible, single cell exceeds T

    int best = 30000;
    int height = r2 - r1 + 1;
    int width = c2 - c1 + 1;

    // Try vertical cuts
    for (int k = c1; k < c2; ++k) {
        best = min(
            best,
            height + solve(r1, c1, r2, k) + solve(r1, k+1, r2, c2)
        );
    }

    // Try horizontal cuts
    for (int k = r1; k < r2; ++k) {
        best = min(
            best,
            width + solve(r1, c1, k, c2) + solve(k+1, c1, r2, c2)
        );
    }

    return memo = best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m >> T;

    vector<vector<int>> grid(n+1, vector<int>(m+1));
    bool impossible = false;

    // Read input and build prefix sums
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] > T) impossible = true;
            prefix_sum[i][j] = grid[i][j] + prefix_sum[i-1][j] + prefix_sum[i][j-1] - prefix_sum[i-1][j-1];
        }
    }

    if (impossible) {
        cout << -1 << '\n';
        return 0;
    }

    memset(dp, -1, sizeof(dp));

    int answer = solve(1, 1, n, m);
    cout << answer << '\n';

    return 0;
}

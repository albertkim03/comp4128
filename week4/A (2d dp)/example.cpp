#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h1(n), h2(n);
    
    for (int &x : h1) cin >> x;
    for (int &x : h2) cin >> x;

    vector<vector<long long>> dp(2, vector<long long>(n, 0));
    dp[0][0] = h1[0];
    dp[1][0] = h2[0];

    long long best_0 = dp[0][0];
    long long best_1 = dp[1][0];

    for (int i = 1; i < n; ++i) {
        dp[0][i] = h1[i] + best_1;
        dp[1][i] = h2[i] + best_0;

        best_0 = max(best_0, dp[0][i]);
        best_1 = max(best_1, dp[1][i]);
    }

    cout << max(best_0, best_1) << endl;
    return 0;
}

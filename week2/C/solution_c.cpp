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

using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<ll> given_array(n);
    vector<ll> given_array_prefix_sum(n);
    unordered_map<ll, int> first_half_counter;
    unordered_map<ll, int> second_half_counter;

    // Initialise everything
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;

        given_array[i] = cur;
        i == 0 ? given_array_prefix_sum[i] = cur : given_array_prefix_sum[i] = given_array_prefix_sum[i - 1] + cur;
        second_half_counter[cur]++;
    }

    // iterate through the given array
    for (int i = 0; i < n; i++) {
        // Add and take away from the counters
        second_half_counter[given_array[i]]--;
        first_half_counter[given_array[i]]++;

        ll first_half_sum = given_array_prefix_sum[i];
        ll second_half_sum = given_array_prefix_sum[n - 1] - given_array_prefix_sum[i];

        // Found match so return YES
        if (first_half_sum == second_half_sum) {
            cout << "YES";
            return 0;
        }
        else {
            ll diff = abs(first_half_sum - second_half_sum);

            // First half is greater than the second half
            if (first_half_sum > second_half_sum 
                && diff % 2 == 0
                && first_half_counter[diff / 2] > 0) 
            {
                cout << "YES";
                return 0;
            } 

            // Second half is greater than the first half
            else if (first_half_sum < second_half_sum 
                && diff % 2 == 0
                && second_half_counter[diff / 2] > 0) 
            {
                cout << "YES";
                return 0;
            }
        }
    }

    cout << "NO";
    return 0;
}

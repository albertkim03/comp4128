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

    int test_cases;
    string current_string;

    cin >> test_cases;


    for (int i = 0; i < test_cases; ++i) {
        cin >> current_string;

        priority_queue<int> longest_continuous_ones;
        int current_length = 0;
        bool ongoing_length = false;
        for (size_t j = 0; j < current_string.size(); j++) {
            if (j == current_string.size() - 1 && current_string[j] == '1') {
                // cout << "HIT";
                current_length += 1;
                longest_continuous_ones.push(current_length);
            }else if (current_string[j] == '1' && ongoing_length == true) {
                current_length += 1;
            } else if (current_string[j] == '1' && ongoing_length == false) {
                ongoing_length = true;
                current_length += 1;
            } else if (current_string[j] == '0' && ongoing_length == true) {
                ongoing_length = false;
                longest_continuous_ones.push(current_length);
                current_length = 0;
            } else if (current_string[j] == '0' && ongoing_length == false) {
                continue;
            } 

        }

        int turn = 0;
        ll total_sum = 0;
        while (!longest_continuous_ones.empty()) {
            // cout << "top: " << longest_continuous_ones.top() << '\n'; 
            if (turn % 2 == 0) {
                total_sum += longest_continuous_ones.top();
            }
            longest_continuous_ones.pop();
            turn += 1;
        }
        cout << total_sum << '\n';
    }

    
    return 0;
}

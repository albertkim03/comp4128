#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
    int t; // number of test cases
    int n; // number of quests
    long long c; // number of coins that i need
    int d; // number of days i get
    cin >> t;

    for (int test_case = 0; test_case < t; test_case ++) {
        // collect n, c, d
        cin >> n >> c >> d;
        multiset<long long> a;

        // collect all quest values array a
        for (int i = 0; i < n; i++) {
            long long stream_value;
            cin >> stream_value;
            a.insert(stream_value);
        }

        long long quest_max = *prev(a.end());
        long long quest_sum = 0;

        // calculate the sum
        auto curr_value = prev(a.end());
        for (int i = 0; i < d; i++) {
            quest_sum += *curr_value;

            if (curr_value == a.begin()) {
                break;
            }

            curr_value = prev(curr_value);
        }

        // I literally do the best quest every day but not enough
        if (quest_max * d < c) { 
            cout << "Impossible" << '\n'; 
            continue;
        }
        
        // If we take the most of the best values we can once and it's better than our goal then k doesn't matter
        if (quest_sum >= c) { 
            cout << "Infinity" << '\n'; 
            continue;
        }

        // Now find the maximum value of k with binary inserts of k
        // Start with middle value of k
        int k;
        int answer = -1;
        int low = 0;
        int high = d;

        while (low <= high) {
            k = low + (high - low) / 2;
            long long quest_accum = 0;

            // Find maximum coins with this value of k
            curr_value = prev(a.end());
            for (int i = 0; i < (k + 1); i++) {
                int positions_left = d - i;
                int max_inserts = positions_left / (k + 1);

                if (positions_left % (k + 1) >= 1) {
                    max_inserts += 1;
                }

                long long max_coins_for_ith_quest = max_inserts * (*curr_value);

                quest_accum += max_coins_for_ith_quest;
    
                if (curr_value == a.begin()) {
                    break;
                }
    
                curr_value = prev(curr_value);
            }
            
            if (quest_accum >= c) {
                answer = k;
                low = k + 1;
            } else if (quest_accum < c) {
                high = k - 1;
            }
        }

        cout << answer << "\n";

    }
}

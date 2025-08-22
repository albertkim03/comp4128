#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {

    int t; 
    int n;
    bool is_positive;
    long long current_max;

    cin >> t;
    vector<long long>solutions(t, 0);


    for (int i = 0; i < t; i++) {
        cin >> n;

        for (int j = 0; j < n; j++) {
            long long current_value;
            cin >> current_value;
            

            // first number that i have seen for this set of numbers
            if (j == 0) {
                is_positive = (current_value > 0);
                current_max = current_value;
            }

            // check if the current number's sign is the same as what we're dealing with 
            if ((current_value > 0) == is_positive) {
                current_max = max(current_max, current_value);
            } else {
                solutions[i] += current_max;
                is_positive = !is_positive;
                current_max = current_value;
            } 

            if (j == (n - 1)) {
                solutions[i] += current_max;
            } 
        }

    }

    for (long long ans : solutions) {
        cout << ans << '\n';
    }
}

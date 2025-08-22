#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int t;
    int n;
    char curr_colour;
    string colours;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;
        cin >> curr_colour;
        cin >> colours;
        
        int longest_total = 0;
        int longest_so_far = 0;

        // current colour is green so just return 0 
        if (curr_colour == 'g') {
            cout << 0 << '\n';

            continue;
        }

        // otherwise go look for the best solution
        for (int j = 0; j < n; j++) {
            // we just found it so reset
            if (colours[j] == curr_colour && longest_so_far == 0) {
                longest_so_far = 1;
                continue;
            }
            
            if (longest_so_far >= 1) {
                longest_so_far += 1;
            }

            longest_total = max(longest_total, longest_so_far - 1);

            if (colours[j] == 'g')  {
                longest_so_far = 0;
            }
        }   

        if (longest_so_far != 0 || colours[n - 1] == curr_colour) {
            for (int j = 0; j < n; j++) {
                // this is the second loop so handle finding the first green
                longest_so_far += 1;
    
                if (colours[j] == 'g') {
                    longest_total = max(longest_so_far - 1, longest_total);
                    break;
                }
            }   
        }

         cout << longest_total << '\n';
    }
}
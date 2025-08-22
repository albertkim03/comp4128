#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    long long t;

    cin >> n;
    cin >> t;

    vector<long long> books(n);
    for (int i = 0; i < n; i++) cin >> books[i];

    int largest_window = 0;

    long long accum = 0;
    int right = -1;

    for (int left = 0; left < n; ++left) {

        while (right + 1 < n && accum + books[right + 1] <= t) {
            ++right;
            accum += books[right];
        }

        largest_window = max(largest_window, right - left + 1);

        if (right >= left) {
            accum -= books[left];
        } else {
            right = left;
        }
    }

    cout << largest_window;
}

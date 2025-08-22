#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {

    int n; 
    int total_cost = 0;
    int current_purchase_price;
    bool fixed_price = false;
    vector<int> a(n);
    vector<int> p(n);
    vector<bool> local_mins(n, false);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> p[i];
    }

    for (int i = 0; i < n; i++) {
        if (i == 0 && n > 1 && p[i] <= p[i + 1]) {
            local_mins[i] = true;
            
        } else if (p[i] <= p[i - 1] && p[i] <= p[i + 1]) {
            local_mins[i] = true;
        }
    }

    for (int i = 0; i < n; i++) {
        // get the new fixed prices
        if (local_mins[i] == true) {
            current_purchase_price = min(current_purchase_price, p[i]);
            fixed_price = true;
        }

        if (fixed_price == true) {
            total_cost += a[i] * min(current_purchase_price, p[i]);
        } else {
            total_cost += a[i] * p[i];
        }

    }

    cout << total_cost << endl;
}
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
    

    int num_array;
    int num_queries;

    cin >> num_array;
    cin >> num_queries;

    priority_queue<ll> array_elements;
    vector<int> array_indexes(num_array + 1);

    // flow of array
    for (int i = 0; i < num_array; ++i) {
        int array_element;
        cin >> array_element;

        array_elements.push(array_element);
    }

    // interval calculations
    for (int i = 0; i < num_queries; ++i) {
        int l;
        int r;
        cin >> l >> r;

        array_indexes[l-1] += 1;
        array_indexes[r-1 + 1] -= 1;
    }

    for (int i = 0; i < num_array; ++i) {
        if (i == 0) {
            continue;
        }
        
        array_indexes[i] += array_indexes[i - 1];
    }

    priority_queue<ll> biggest_indexes;
    for (int i = 0; i < num_array ; ++i) {
        biggest_indexes.push(array_indexes[i]);
    }

    ll total = 0;
    for (int i = 0; i < num_array ; ++i) {

        total += biggest_indexes.top() * array_elements.top(); 
        biggest_indexes.pop();
        array_elements.pop();
    }

    // for (auto cur_val : biggest_indexes) {
    //     cout << cur_val << "\n";
    // }
    cout << total;

    return 0;
}

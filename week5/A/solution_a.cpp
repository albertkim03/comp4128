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
#include <list>


using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // number of employees
    int n; cin >> n; 
    
    // ith employee qualification
    vector<int> ith_qualification(n);
    for (auto &x : ith_qualification) cin >> x;

    // number of applications
    int m; cin >> m;

    // appplications
    unordered_map<int, int> pair_to_cost;


    for (int i = 0; i < m; ++i) {
        int a;
        int b;
        int c;
        cin >> a >> b >> c;

        if ((pair_to_cost.count(b) > 0 && pair_to_cost[b] > c) || pair_to_cost.count(b) == 0) {
            pair_to_cost[b] = c;
        }
    }

    // there is more than 1 person with no supervisor (impossible)
    if ((int)pair_to_cost.size() + 1 != n) {
        cout << -1;
        return 0;
    }

    ll total = 0;
    for (auto p_to_c : pair_to_cost) {
        total += p_to_c.second;
    }

    cout << total;

    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_a solution_a.cpp
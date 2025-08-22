// g++-15 -Wall -std=c++17 -o solution solution.cpp

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

    ll student_count;

    cin >> student_count;

    // [departure_time, skill]
    vector<pair<ll, ll>> time_and_skill;

    for (int i = 0; i < student_count; ++i) {
        ll temp_skill;
        ll temp_departure;

        cin >> temp_skill >> temp_departure;

        time_and_skill.push_back(pair<ll, ll>(temp_departure, temp_skill));
    }

    sort(time_and_skill.begin(), time_and_skill.end());

    ll total_entertainment = 0;

    // always know the lowest skill
    priority_queue<ll, vector<ll>, greater<ll>> min_heap;

    for (pair<ll, ll> cur_student : time_and_skill) {
        ll temp_skill = cur_student.second;
        ll temp_departure = cur_student.first;

        min_heap.push(temp_skill);
        total_entertainment += temp_skill;

        if ((ll)min_heap.size() > temp_departure) {
            // remove the lowest skill, replacing it with the one we just added unless its the same thing
            total_entertainment -= min_heap.top();
            min_heap.pop();
        }
    }

    cout << total_entertainment << '\n';

    return 0;
}

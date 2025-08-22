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

const int START_TIME = 1;
const int END_TIME = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_of_activities;
    int number_of_classrooms;
    int total_count = 0;

    cin >> number_of_activities >> number_of_classrooms;

    // fill multiset classrooms
    multiset<ll> classrooms;

    for (ll i = 0; i < number_of_classrooms; i++) {
        classrooms.insert(0);
    }

    // receieve and sort activities 
    vector<pair<ll, ll>> activities;
    
    for (int i = 0; i < number_of_activities; i++) {
        ll start_time;
        ll end_time;

        cin >> start_time >> end_time;

        activities.push_back(make_pair(end_time, start_time));
    }
    sort(activities.begin(), activities.end());

    // iterate through each activity sorted by ascending end time
    for (const auto &activity : activities) {
        auto [end_time, start_time] = activity;

        // binary search to find the first classroom ending less than this current activity start
        auto current_end_time_iterator = classrooms.lower_bound(start_time);

        if (current_end_time_iterator == classrooms.begin()) {
            continue;
        }

        // found a valid insertion option
        total_count += 1;

        current_end_time_iterator = prev(current_end_time_iterator);
        ll current_end_time = *current_end_time_iterator;

        // erase the iterator not the ones that match
        classrooms.erase(classrooms.find(current_end_time));
        classrooms.insert(end_time);
    }

    cout << total_count;

    return 0;
}

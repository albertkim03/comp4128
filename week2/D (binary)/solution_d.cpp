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
typedef tuple<ll, ll, int> student_tuple;
const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

// [Skill, pass, index]
set<tuple<ll, ll, int>> used_student_list;

// pair of [bug complexity | index]
vector<pair<ll, int>> bug_list;

bool test_possible(int num_days) {
    int bug_index = (int)bug_list.size() - 1;

    for (auto [temp_skill, temp_pass, temp_index] : used_student_list) {
        int count = 0;

        // as long as the current student can do the bug
        while (bug_index >= 0 && temp_skill >= get<0>(bug_list[bug_index]) && count < num_days) {
            count += 1;
            bug_index -= 1;
        }
    }

    if (bug_index == -1) {
        return true;
    } else {
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // initialise the first line
    int number_of_students;
    int number_of_bugs;
    ll max_number_of_passes;
    ll most_skillful_student = 0;

    cin >> number_of_students >> number_of_bugs >> max_number_of_passes;


    for (int i = 0; i < number_of_bugs; ++i) {
        ll bug_complexity;
        cin >> bug_complexity;

        bug_list.push_back(pair<ll, int>(bug_complexity, i + 1));
    }
    sort(bug_list.rbegin(), bug_list.rend());

    // tuple of [student pass | student skill | index]
    vector<tuple<ll, ll, int>> temp_student_list(number_of_students);
    for (int i = 0; i < number_of_students; ++i) { // initialise skill + index
        ll skill;
        cin >> skill;
        auto& [tuple_pass, tuple_skill, tuple_index] = temp_student_list[i];

        most_skillful_student = max(most_skillful_student, skill);

        tuple_skill = skill;
        tuple_index = i + 1;
    }
    for (int i = 0; i < number_of_students; ++i) { // initialise pass request
        ll pass;
        cin >> pass;
        auto& [tuple_pass, tuple_skill, tuple_index] = temp_student_list[i];

        tuple_pass = pass;
    }

    // tuple of [student pass | student skill | index] (ascending pass)
    set<tuple<ll, ll, int>>student_list(temp_student_list.begin(), temp_student_list.end());


    // index
    unordered_set<int> used_student_index;

    ll pass_sum = 0;

    // hardest bug > most skillfull student
    if (get<0>(bug_list[0]) > most_skillful_student) {
        cout << "NO\n";
        return 0;
    }

    // go to through the bug complexities hardest->easiest
    for (auto [bug_complexity, bug_index] : bug_list) {

        for (const auto& it : student_list) {
            ll cur_pass = get<0>(it);
            ll cur_skill = get<1>(it);
            int cur_index = get<2>(it);
            
            // found someone good enough and we haven't used them before
            if (cur_skill >= bug_complexity && used_student_index.count(cur_index) == 0) {  
                // hardest bugs solver is too expensive
                if (pass_sum == 0 && cur_pass > max_number_of_passes) {
                    cout << "NO\n";
                    return 0;
                }

                //too expensive
                if (pass_sum + cur_pass > max_number_of_passes) {
                    break;
                }

                pass_sum += cur_pass;
                used_student_index.insert(cur_index);

                used_student_list.insert(student_tuple(cur_skill, cur_pass, cur_index));
                break;
            }
        }
    }

    // initialise binary search
    int lowest_possible_day = number_of_students;
    int left = 1;
    int right = number_of_students;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        bool result = test_possible(mid);

        if (result) {
            lowest_possible_day = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    vector<int> bug_to_student(number_of_bugs + 1);

    int bug_index2 = (int)bug_list.size() - 1;

    for (auto [temp_skill, temp_pass, temp_index] : used_student_list) {
        int count = 0;

        // as long as the current student can do the bug
        while (bug_index2 >= 0 && temp_skill >= get<0>(bug_list[bug_index2]) && count < lowest_possible_day) {
            int bug_original_index = get<1>(bug_list[bug_index2]);  // the 1-based index
            bug_to_student[bug_original_index] = temp_index; 
            count += 1;
            bug_index2 -= 1;
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= number_of_bugs; ++i) {
        cout << bug_to_student[i] << " ";
    }
    cout << "\n";

    // cout << "!!!!!!!!!!\n";

    // bool new_result = test_possible(3);

    // cout << new_result;
    // for (const auto& [skill, pass, index] : used_student_list) {
    //     cout << "[" << skill << ", " << pass << ", " << index << "]" << endl;
    // }

    return 0;
}

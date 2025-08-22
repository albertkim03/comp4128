
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
using ll = long long;

struct Bug {
    ll complexity;
    int id;
};
struct Student {
    ll skill;
    ll pass;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; ll S;
    if (!(cin >> n >> m >> S)) return 0;

    //read in bugs
    vector<Bug> bugs(m);
    for (int i = 0; i < m; ++i) {
        cin >> bugs[i].complexity;
        bugs[i].id = i + 1;
    }
    sort(bugs.begin(), bugs.end(),
         [](const Bug& a, const Bug& b) { return a.complexity > b.complexity; });

    //reead in student
    vector<Student> students(n);
    for (int i = 0; i < n; ++i)  cin >> students[i].skill;
    for (int i = 0; i < n; ++i)  cin >> students[i].pass, students[i].id = i + 1;

    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) { return a.skill > b.skill; });

    if (bugs[0].complexity > students[0].skill) {  // hardest bug unsolvable
        cout << "NO\n"; return 0;
    }

    // see if possible
    auto feasible = [&](int D, vector<int>* assignment) -> ll {
        ll totalPass = 0;
        priority_queue< pair<ll,int>,
                        vector<pair<ll,int>>,
                        greater<pair<ll,int>> > heap;   // (pass, studentIndex)
        vector<int> tmp(m + 1, 0);                    // bug id → student id

        int stuPtr = 0;
        for (int i = 0; i < m; i += D) {
            ll needComplex = bugs[i].complexity;
            while (stuPtr < n && students[stuPtr].skill >= needComplex) {
                heap.emplace(students[stuPtr].pass, stuPtr);
                ++stuPtr;
            }
            if (heap.empty()) return -1;              // no capable student

            auto [passCost, idx] = heap.top(); heap.pop();
            totalPass += passCost;
            if (totalPass > S) return -1;             // budget exceeded

            int sid = students[idx].id;
            for (int k = i; k < i + D && k < m; ++k)
                tmp[bugs[k].id] = sid;
        }
        if (assignment) *assignment = move(tmp);
        return totalPass;
    };

    // binary search possible days
    int lo = 1, hi = m, bestD = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid, nullptr) != -1) {
            bestD = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (bestD == -1) {           // never feasible
        cout << "NO\n";
        return 0;
    }

    
    vector<int> answer;
    feasible(bestD, &answer);

    cout << "YES\n";
    for (int i = 1; i <= m; ++i) {
        cout << answer[i] << (i == m ? '\n' : ' ');
    }
    return 0;
}

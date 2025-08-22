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
#include <utility>
#include <functional>   

struct pair_hash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1,T2>& p) const noexcept
    {
        // hash the two parts and mix them.
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);

        // use: unordered_map<std::pair<int,int>, int, pair_hash> dist;
        //     visited.insert({0,0});
        //     visited.insert({1,1});
        //     std::pair<int,int> p{0,0};
        //     if (visited.count(p)) std::cout << "(0,0) already visited\n";
        return h1 ^ (h2 << 1);
    }
};

using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int LEFT = 0;
    const int RIGHT = 1;
    const int SEEN = 1;

    int n; cin >> n;
    int k; cin >> k;

    vector<vector<char>> wall(2, vector<char>(n, '0'));
    vector<vector<int>> seen_wall(2, vector<int>(n, 0));


    // left wall
    for (int i = 0; i < n; ++ i) {
        char item; cin >> item;
        wall[LEFT][i] = item;

        if (item == 'X') {
            seen_wall[LEFT][i] = SEEN;
        }
    }

    // right wall
    for (int i = 0; i < n; ++ i) {
        char item; cin >> item;
        wall[RIGHT][i] = item;

        if (item == 'X') {
            seen_wall[RIGHT][i] = SEEN;
        }
    }

    // [wall side, x, time]
    deque<tuple<int, int, int>> position_dequeue;
    position_dequeue.push_back(tuple<int, int, int>(LEFT, 0, 0));
    
    while (position_dequeue.size() != 0) {
        // current wall
        tuple<int, int, int> current_position = position_dequeue.front();
        position_dequeue.pop_front();

        // get each item
        int cur_side = get<0>(current_position);
        int cur_index = get<1>(current_position);
        int cur_time = get<2>(current_position);
        
        // seen or skip
        if (seen_wall[cur_side][cur_index] == SEEN || cur_index < cur_time) {
            continue;
        } else {
            seen_wall[cur_side][cur_index] = SEEN;
        }

        // our win condition
        if (cur_index == n - 1) {
            cout << "YES";
            return 0;
        }

        // queue each possible move
        // go right (if we haven't seen it and not a spike)
        if (cur_index + 1 >= n) {
            cout << "YES";
            return 0;
        }
        if (cur_index + 1 < n && seen_wall[cur_side][cur_index + 1] != SEEN) {

            position_dequeue.push_back(tuple<int, int, int>(cur_side, cur_index + 1, cur_time + 1));
        }

        // go left (if we haven't seen it and not a spike and we won't be flooded)
        if (cur_index - 1 >= 0 && seen_wall[cur_side][cur_index - 1] != SEEN && cur_time + 1 <= cur_index - 1) {
            position_dequeue.push_back(tuple<int, int, int>(cur_side, cur_index - 1, cur_time + 1));
        }

        // jump
        if (cur_index + k >= n) {
            cout << "YES";
            return 0;
        }
        if (cur_index + k < n && seen_wall[!cur_side][cur_index + k] != SEEN) {

            position_dequeue.push_back(tuple<int, int, int>(!cur_side, cur_index + k, cur_time + 1));
        }

    }

    cout << "NO";

    return 0;
}



// g++-15 -Wall -std=c++17 -o solution_a solution_a.cpp
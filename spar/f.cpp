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
int n; 
vector<vector<char>> flowers(n, vector<char>(n, 'z'));
unordered_set<string> seen_necklaces;


bool necklace_recurse(int i, int k, string current_necklace, vector<vector<char>> &flowers, unordered_set<string> &seen_necklaces) {
    // base case
    if ((int)current_necklace.length() == n) {
        if (seen_necklaces.count(current_necklace) > 0) {
            return true;
        } else {
            seen_necklaces.insert(current_necklace);
            return false;
        }
    }

    bool seen1, seen2;

    if (k < n - 1) {
        seen1 = necklace_recurse(i, k + 1, current_necklace + flowers[i][k + 1], flowers, seen_necklaces);
    }

    if (i < n - 1) {
        seen2 = necklace_recurse(i + 1, k, current_necklace + flowers[i + 1][k], flowers, seen_necklaces);
    }

    return seen1 || seen2;
}


int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    vector<vector<char>> flowers(n, vector<char>(n, 'z'));
    unordered_set<string> seen_necklaces;


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char cell;
            cin >> cell;

            flowers[i][j] = cell;
        }
    }

    necklace_recurse(0, 0, "", flowers, seen_necklaces) ? cout << "duplicates" : cout << "unique";

    return 0;
}



// g++-15 -Wall -std=c++17 -o a a.cpp
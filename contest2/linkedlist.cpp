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

#include <numeric>
using namespace std;
typedef long long ll;

const ll INF = (1LL << 61);
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =1e5+10;

// union find
struct DisjointSetUnion {
    vector<int> parent;
    vector<int> set_size;

    DisjointSetUnion(int number_of_vertices = 0) {
        parent.resize(number_of_vertices + 1);
        set_size.assign(number_of_vertices + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find_leader(int vertex) {
        if (parent[vertex] == vertex) return vertex;
        return parent[vertex] = find_leader(parent[vertex]);
    }
    void unite_sets(int vertex_a, int vertex_b) {
        vertex_a = find_leader(vertex_a);
        vertex_b = find_leader(vertex_b);
        if (vertex_a == vertex_b) return;
        if (set_size[vertex_a] < set_size[vertex_b]) swap(vertex_a, vertex_b);
        parent[vertex_b] = vertex_a;
        set_size[vertex_a] += set_size[vertex_b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_of_users, number_of_queries;
    cin >> number_of_users >>  number_of_queries; 

    vector<int> boss(number_of_users + 1);
    vector<int> depth(number_of_users + 1);
    vector<int> next_unmerged(number_of_users + 1);

    boss[1]  = 1;
    depth[1] = 0;
    for (int user = 2; user <= number_of_users; ++user) {
        cin >> boss[user];
        depth[user]          = depth[boss[user]] + 1;
        next_unmerged[user]  = boss[user];
    }
    next_unmerged[1] = 1;

    // Initialise union-find
    DisjointSetUnion dsu(number_of_users);

    auto merge_upward_one_step = [&](int& user) {
        if (user == 1) return;
        int direct_boss = boss[user];
        dsu.unite_sets(user, direct_boss);
        next_unmerged[user] = next_unmerged[direct_boss];
        user = next_unmerged[user];
    };

    // merge every chat
    auto merge_entire_path = [&](int user_x, int user_y) {
        if (dsu.find_leader(user_x) == dsu.find_leader(user_y)) return;

        int pointer_a = user_x;
        int pointer_b = user_y;

        while (depth[pointer_a] > depth[pointer_b])
            merge_upward_one_step(pointer_a);
        while (depth[pointer_b] > depth[pointer_a])
            merge_upward_one_step(pointer_b);

        while (pointer_a != pointer_b) {
            merge_upward_one_step(pointer_a);
            merge_upward_one_step(pointer_b);
        }

        // make sure invite to x gorup
        dsu.unite_sets(user_x, pointer_a);
    };


    while (number_of_queries--) {
        int query_type, user_x, user_y;
        cin >> query_type >> user_x >> user_y;

        if (query_type == 1) {
            dsu.unite_sets(user_x, user_y);

        } else if (query_type == 2) {
            merge_entire_path(user_x, user_y);

        } else if (query_type == 3) {
            if (dsu.find_leader(user_x) == dsu.find_leader(user_y))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}

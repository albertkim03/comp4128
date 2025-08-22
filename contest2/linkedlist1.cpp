#include <bits/stdc++.h>
using namespace std;

/* ------------------------------------------------------------------
   Disjoint-Set Union (union–find) to maintain current group-chat sets
   ------------------------------------------------------------------ */
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
/* ------------------------------------------------------------------ */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_of_users, number_of_queries;
    if (!(cin >> number_of_users >> number_of_queries)) return 0;

    /* --------------------------------------------------------------
       Read the boss hierarchy and pre-compute depth information
       -------------------------------------------------------------- */
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

    /* --------------------------------------------------------------
       Initialise the union–find structure
       -------------------------------------------------------------- */
    DisjointSetUnion dsu(number_of_users);

    /* --------------------------------------------------------------
       Helper: lift one step upward, merging the current user’s chat
       with that of its direct boss, and shortcutting the pointer
       -------------------------------------------------------------- */
    auto merge_upward_one_step = [&](int& user) {
        if (user == 1) return;
        int direct_boss = boss[user];
        dsu.unite_sets(user, direct_boss);
        next_unmerged[user] = next_unmerged[direct_boss];
        user = next_unmerged[user];
    };

    /* --------------------------------------------------------------
       Helper: merge every chat on the (unique) tree path between
       user_x and user_y into user_x’s chat
       -------------------------------------------------------------- */
    auto merge_entire_path = [&](int user_x, int user_y) {
        if (dsu.find_leader(user_x) == dsu.find_leader(user_y)) return;

        int pointer_a = user_x;
        int pointer_b = user_y;

        /* lift the deeper pointer so depths align */
        while (depth[pointer_a] > depth[pointer_b])
            merge_upward_one_step(pointer_a);
        while (depth[pointer_b] > depth[pointer_a])
            merge_upward_one_step(pointer_b);

        /* climb both pointers together until they meet */
        while (pointer_a != pointer_b) {
            merge_upward_one_step(pointer_a);
            merge_upward_one_step(pointer_b);
        }

        /* make sure the meeting node’s chat joins user_x’s chat */
        dsu.unite_sets(user_x, pointer_a);
    };

    /* --------------------------------------------------------------
       Process queries
       -------------------------------------------------------------- */
    while (number_of_queries--) {
        int query_type, user_x, user_y;
        cin >> query_type >> user_x >> user_y;

        if (query_type == 1) {
            dsu.unite_sets(user_x, user_y);

        } else if (query_type == 2) {
            merge_entire_path(user_x, user_y);

        } else {   /* query_type == 3 */
            if (dsu.find_leader(user_x) == dsu.find_leader(user_y))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
    return 0;
}

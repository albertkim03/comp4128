#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int n;

vector<int> adj[N];
int in[N], out[N], euler[N], val[N], comp[N], ans[N];
int timer = 0;

struct SegmentTree {
    int n;
    vector<vector<int>> tree;

    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    void build(const vector<int>& data, int node, int l, int r) {
        if (l == r) {
            tree[node] = { data[l] };
        } else {
            int mid = (l + r) / 2;
            build(data, 2 * node, l, mid);
            build(data, 2 * node + 1, mid + 1, r);
            merge(tree[2 * node].begin(), tree[2 * node].end(),
                  tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
                  back_inserter(tree[node]));
        }
    }

    int query(int node, int l, int r, int ql, int qr, int val) {
        if (r < ql || l > qr) return 0;
        if (ql <= l && r <= qr) {
            return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), val);
        }
        int mid = (l + r) / 2;
        return query(2 * node, l, mid, ql, qr, val) +
               query(2 * node + 1, mid + 1, r, ql, qr, val);
    }

    int query(int ql, int qr, int val) {
        return query(1, 0, n - 1, ql, qr, val);
    }
};

// Flatten the tree
void dfs(int u, int parent) {
    in[u] = timer;
    euler[timer] = u;
    ++timer;
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
        }
    }
    out[u] = timer;
}

int main() {

    freopen("promote.in", "r", stdin);
    freopen("promote.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    vector<int> all_vals;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        all_vals.push_back(val[i]);
    }

    for (int i = 2; i <= n; ++i) {
        int parent;
        cin >> parent;
        adj[parent].push_back(i);
        adj[i].push_back(parent);
    }

    // Coordinate compression
    sort(all_vals.begin(), all_vals.end());
    map<int, int> compress;
    int id = 1;
    for (int x : all_vals) {
        if (compress.count(x) == 0) {
            compress[x] = id++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        comp[i] = compress[val[i]];
    }

    dfs(1, -1);

    // Flattened tree using compressed skills
    vector<int> flat(n);
    for (int i = 0; i < n; ++i) {
        flat[i] = comp[euler[i]];
    }

    // Build segment tree
    SegmentTree st(flat);

    // Query for each node
    for (int u = 1; u <= n; ++u) {
        int l = in[u];
        int r = out[u] - 1;
        ans[u] = st.query(l, r, comp[u]);
    }

    // Output results
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }

    return 0;
}

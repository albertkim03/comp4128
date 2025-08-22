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

        int n, m, k;
        long long c;
        cin >> n >> m >> k >> c;

        // cin happiness
        vector<vector<ll>> hipppo_happiness(n, vector<ll>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> hipppo_happiness[i][j];
            }
        }
            
        // cin hippo friends
        vector<int> hippo_friends(n, -1);
        for (int e = 0; e < k; ++e) {
            int u, v; cin >> u >> v;
            u -= 1;
            v -= 1;
            hippo_friends[u] = v;
            hippo_friends[v] = u;
        }

        vector<char> seen(n, false);
        long long solution = 0;

        for (int i = 0; i < n; ++i) {
            if (seen[i]) continue;

            int j = hippo_friends[i];
            if (j == -1) {
                solution += *max_element(hipppo_happiness[i].begin(), hipppo_happiness[i].end());
                seen[i] = true;
            } else {
                seen[j] = true;
                seen[i] = true;

                // prefix and suffic max
                vector<ll> prefix(m);
                vector<ll> suffix(m);

                // precompute left to right max
                for (int k = 0; k < m; ++k) {
                    ll val = hipppo_happiness[j][k] + (1LL * c * k);
                    prefix[k] = (k == 0) ? val : max(prefix[k-1], val);
                }
                // precompute right to left max
                for (int k = m-1; k >= 0; --k) {
                    ll val = hipppo_happiness[j][k] - (1LL * c * k);
                    suffix[k] = (k == m-1) ? val : max(suffix[k + 1], val);
                }

                long long best_pair = -INF;
                for (int k = 0; k < m; ++k) {
                    // b greater a branch
                    ll g_left  = prefix[k] - (1LL * c * k);
                    
                    // b greater branch
                    ll g_right = suffix[k] + (1LL*c * k);
                    ll g = max(g_left, g_right);
                    best_pair = max(best_pair, hipppo_happiness[i][k] + g);
                }
                solution = solution + best_pair;
            }
        }

        cout << solution;
        return 0;
    }

    // g++-15 -Wall -std=c++17 -o hippo-ponds hippo-ponds.cpp
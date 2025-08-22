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
// const int INF = (1LL << 30);
// const int INF = 1e9;

const ll N = 200010;
ll parent[N], subtreeSize[N];

void init(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        subtreeSize[i] = 1;
    }
}

// with path compression
// amortized O(α(n)) - inverse ackernman function, which is <= 5 for any conceivable n
// int root(int x) {
//    return parent[x] == x ? x : parent[x] = root(parent[x]);
// }

// same as above function - expanded for readability
int root(int x) {
    if (parent[x] == x) {
        return x;
    }

    // recursively obtain root
    int rootX = root(parent[x]);
    
    // path compression - attach x directly to root
    parent[x] = rootX;

    return rootX;
}


// amortized O(α(n)) - inverse ackernman function, which is <= 5 for any conceivable n
// join with size heuristic
void join(int x, int y)  {
    x = root(x); y = root(y);

    // if already connected, return
    if (x == y) return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtreeSize[x] < subtreeSize[y]) {
        parent[x] = y;
        subtreeSize[y] += subtreeSize[x];
    } else  {
        parent[y] = x;
        subtreeSize[x] += subtreeSize[y];
    }

}


int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];
    
    // start union-find tree
    init(n);

    vector<int> rep(26, -1);

    for (int i = 0; i < n; ++i) {
        vector<bool> seen(26, false);

        // for each letter in current password
        for (char ch : s[i]) {
            // mark unique characters
            seen[ch - 'a'] = true;
        }

        for (int c = 0; c < 26; ++c) {
            if (!seen[c]) continue;
            
            // let the representative of this character in the alphabet
            // be the id of the string we're currently looking at
            if (rep[c] == -1) {
                rep[c] = i;
            } else {

                //otherwise join the id of the current string we're looking at 
                // with teh id of the representative id of the current character we're looking at
                join(i, rep[c]);
            }

        }


    }

    unordered_set<int> roots;

    for (int i = 0; i < n; ++i) {

        // find the root of every id of every string
        roots.insert(root(i));
    }

    cout << roots.size();




    
    return 0;
}



// g++-15 -Wall -std=c++17 -o week_2_a week_2_a.cpp
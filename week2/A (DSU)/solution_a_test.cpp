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

int parent[26]; // letters

int find_parent(int x) {
    return parent[x] == x ? x : parent[x] = find_parent(parent[x]);
}

void unite_letters(char a, char b) {
    int pa = find_parent(a - 'a');
    int pb = find_parent(b - 'a');
    if (pa != pb) parent[pa] = pb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> passwords(n);
    unordered_set<int> used_components;

    // each letter is its own parent
    for (int i = 0; i < 26; ++i) parent[i] = i;

    for (int i = 0; i < n; ++i) {
        cin >> passwords[i];

        // connect all letters in the same password
        string& word = passwords[i];
        for (size_t j = 1; j < word.size(); ++j) {
            unite_letters(word[0], word[j]);
        }
    }

    // mark unique connected letters used by at least one password
    for (const auto& word : passwords) {
        for (char ch : word) {
            used_components.insert(find_parent(ch - 'a'));
            break;
        }
    }

    cout << used_components.size() << '\n';

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string word;
    if (!(cin >> n >> word)) return 0;
    int m = word.size();

    vector<string> g(n);
    for (auto &row : g) cin >> row;

    // 1 letter input
    if (m == 1) {
        long long cnt = 0;
        for (auto &row : g)
            for (char ch : row)
                if (ch == word[0]) ++cnt;
        cout << cnt << '\n';
        return 0;
    }

    const int dx[8] = {0,0,1,-1, 1,1,-1,-1};
    const int dy[8] = {1,-1,0,0, 1,-1,1,-1};

    set<vector<pair<int,int>>> seen;
    long long ans = 0;

    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            for (int dir = 0; dir < 8; ++dir) {

                vector<pair<int,int>> path;
                int x = r, y = c, k = 0;
                while (k < m && 0 <= x && x < n && 0 <= y && y < n &&
                       g[x][y] == word[k]) {
                    path.emplace_back(x,y);
                    x += dx[dir]; y += dy[dir];
                    ++k;
                }
                if (k != m) continue;

                auto rev = path;
                reverse(rev.begin(), rev.end());
                const auto &canon = min(path, rev);

                if (seen.insert(canon).second)
                    ++ans;
            }

    cout << ans << '\n';
}

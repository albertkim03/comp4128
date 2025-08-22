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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string cur_str;
    unordered_map<string, int> letter_to_id;
    unordered_multimap<int, string> id_to_words;

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        string key(1, ch);
        letter_to_id[key] = ch - 'a' + 1;
    }
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> cur_str;

        string first_letter{cur_str[0]};
        int this_word_id = letter_to_id[first_letter];

        // iterate through each letter
        for (size_t j = 0; j < cur_str.size(); ++j) {
            string this_letter(1, cur_str[j]);

            int prev_id = letter_to_id[this_letter];
            letter_to_id[this_letter] = this_word_id;

            auto range = id_to_words.equal_range(prev_id);
            for (auto it = range.first; it != range.second; ++it) {
                id_to_words.insert({this_word_id, it->second});
            }

            id_to_words.erase(range.first, range.second);
        }

        id_to_words.insert({this_word_id, cur_str});
    }

    unordered_set<int> ids;
    for (auto &[s, id] : id_to_words) {
        ids.insert(s);
    }

    cout << ids.size();

    return 0;
}

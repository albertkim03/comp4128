#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    struct Stamp { long long pos; int id; };
    vector<Stamp> stamps(n);
    for (int i = 0; i < n; ++i) {
        cin >> stamps[i].pos;
        stamps[i].id = i + 1;
    }

    // sort positioning
    sort(stamps.begin(), stamps.end(),
              [](const Stamp& a, const Stamp& b) {
                  return a.pos < b.pos;
              });

    // create order

    vector<int> order;
    order.reserve(n);

    int mid = (n - 1) / 2;
    order.push_back(stamps[mid].id);

    for (int off = 1; static_cast<int>(order.size()) < n; ++off) {
        if (mid + off < n)
            order.push_back(stamps[mid + off].id);
        if (mid - off >= 0 && static_cast<int>(order.size()) < n)
            order.push_back(stamps[mid - off].id);
    }

    //output
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << order[i];
    }
    cout << '\n';

    return 0;
}

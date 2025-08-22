#include <bits/stdc++.h>                 // grab common STL headers in one go
using namespace std;

struct Pt { long long x, y; };          // lattice point with 64-bit coords

// Oriented area (cross product) for three points: (b - a) x (c - a).
// Use __int128 to avoid overflow since |x|,|y| ≤ 1e9 and products can hit 1e18.
static inline __int128 cross3(const Pt& a, const Pt& b, const Pt& c) {
    return (__int128)(b.x - a.x) * (c.y - a.y)   // (bx-ax)*(cy-ay)
         - (__int128)(b.y - a.y) * (c.x - a.x);  // - (by-ay)*(cx-ax)
}

// Test if all points can be covered by two lines when the first line is fixed
// by points p[i] and p[j].
bool check_pair(const vector<Pt>& p, int i, int j) {
    vector<int> bad;                              // indices not on line (i,j)
    bad.reserve(p.size());                        // avoid reallocations

    for (int k = 0; k < (int)p.size(); ++k) {     // scan all points
        if (cross3(p[i], p[j], p[k]) != 0)        // nonzero => not collinear with (i,j)
            bad.push_back(k);                     // collect “off-line” points
    }

    if ((int)bad.size() <= 2) return true;        // ≤2 points always lie on one line

    int u = bad[0], v = bad[1];                   // define the second line by first two bads
    for (int idx : bad) {                         // verify all remaining bads are collinear
        if (cross3(p[u], p[v], p[idx]) != 0)      // any nonzero => needs a third line
            return false;                         // not coverable by just two lines
    }
    return true;                                  // all bad points collinear => YES for this pair
}

int main() {
    ios::sync_with_stdio(false);                  // fast IO
    cin.tie(nullptr);                             // untie cin/cout

    int n;                                        // number of points
    if (!(cin >> n)) return 0;                    // read n; exit if input ends

    vector<Pt> p(n);                               // store points
    for (int i = 0; i < n; ++i)                   // read n lattice points
        cin >> p[i].x >> p[i].y;

    if (n <= 4) {                                 // small cases always YES
        cout << "YES\n";
        return 0;
    }

    // Try three candidate choices for the first line:
    // (p0,p1), (p0,p2), and (p1,p2). If any works, answer is YES.
    bool ok = check_pair(p, 0, 1)                 // first candidate line
           || check_pair(p, 0, 2)                 // second candidate line
           || check_pair(p, 1, 2);                // third candidate line

    cout << (ok ? "YES\n" : "NO\n");              // print result
    return 0;                                     // done
}

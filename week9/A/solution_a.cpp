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

    int n; 
    if (!(cin >> n)) return 0;
    struct Pt { long long x, y; int id; };

    vector<Pt> a(n);
    for (int i = 0; i < n; ++i) {
        long long x, y; 
        cin >> x >> y;
        a[i] = {x, y, i + 1};   // keep original 1-based index
    }

    // 1) choose pivot = leftmost, then lowest
    int p = 0;
    for (int i = 1; i < n; ++i)
        if (a[i].x < a[p].x || (a[i].x == a[p].x && a[i].y < a[p].y))
            p = i;
    swap(a[0], a[p]);
    Pt pivot = a[0];

    // 2) sort others by polar angle around pivot (no atan2)
    auto half = [](long long dx, long long dy) -> int {
        // upper half-plane (y>0) and +x axis first
        return (dy > 0 || (dy == 0 && dx >= 0)) ? 0 : 1;
    };
    auto cmp = [&](const Pt& U, const Pt& V) -> bool {
        long long ux = U.x - pivot.x, uy = U.y - pivot.y;
        long long vx = V.x - pivot.x, vy = V.y - pivot.y;

        int hu = half(ux, uy), hv = half(vx, vy);
        if (hu != hv) return hu < hv;

        ll cr = (ll)ux * vy - (ll)uy * vx; // cross((ux,uy),(vx,vy))
        if (cr != 0) return cr > 0;                          // CCW first

        // same ray: nearer first
        unsigned long long du = (unsigned long long)ux*ux + (unsigned long long)uy*uy;
        unsigned long long dv = (unsigned long long)vx*vx + (unsigned long long)vy*vy;
        return du < dv;
    };
    sort(a.begin() + 1, a.end(), cmp);

    // 3) pick q and first non-collinear r
    auto cross3 = [](const Pt& A, const Pt& B, const Pt& C) -> ll {
        return (ll)(B.x - A.x) * (C.y - A.y)
             - (ll)(B.y - A.y) * (C.x - A.x);
    };

    Pt q = a[1];
    int j = 2;
    while (j < n && cross3(pivot, q, a[j]) == 0) ++j;

    // Problem is typically guaranteed "not all collinear"; if it isn't, j==n would happen.
    // You can assert or handle as needed. Here we just guard to avoid UB.
    if (j == n) j = 2;

    cout << pivot.id << ' ' << q.id << ' ' << a[j].id << '\n';
    return 0;
}

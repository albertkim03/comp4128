#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
#include <map>
#include <unordered_map>
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
// const int INF = (1LL << 30);
// const int INF = 1e9;

const ll MOD = 1000 * 1000 * 1000 + 7;

typedef pair<ll, ll> pt;

const double EPS = 1e-8;
#define x first
#define y second

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

// if cross(a,b) == 0 -> collinear
double cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

// true if left or straight
// sometimes useful to instead return an int
// -1, 0 or 1: the sign of the cross product
bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) >= 0;
}

/* ******************************************
 * segment segment intersection
 * ******************************************
 */

typedef pair<pt, pt> seg;

bool collinear(seg ab, seg cd) { // all four points collinear
  pt a = ab.first, b = ab.second, c = cd.first, d = cd.second;
  return zero(cross(b - a, c - a)) &&
         zero(cross(b - a, d - a));
}


double sq(double t) { return t * t; }

double dist(pt p, pt q) { return sqrt(sq(p.x - q.x) + sq(p.y - q.y)); }

bool intersect(seg ab, seg cd) {
  pt a = ab.first, b = ab.second, c = cd.first, d = cd.second;
  
  if (collinear(ab, cd)) {
    double maxDist = max({dist(a, b), dist(a, c), dist(a, d),
                          dist(b, c), dist(b, d), dist(c, d)});
    return maxDist < dist(a, b) + dist(c, d) + EPS;
  }

  // only finds proper intersections
  // for non-proper, have ccw return an int
  // then return whether both products of ccws are <= 0
  return ccw(a, b, c) != ccw(a, b, d) &&
         ccw(c, d, a) != ccw(c, d, b);
}






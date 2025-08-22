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

// typedef pair<ll, ll> pt;
typedef pair<double, double> pt;

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

// Alternatively, see 8D for half plane equations and code
bool inTriangle(pt &a, pt &b, pt &c, pt &d) {
    // Compute total area of triangle ABC
    double abc = fabs(cross(b - a, c - a));
    
    // Compute areas of sub-triangles
    double abd = fabs(cross(b - a, d - a));
    double acd = fabs(cross(c - a, d - a));
    double bcd = fabs(cross(c - b, d - b));

    // Check if sum of sub-triangle areas equals total area
    return zero(abc - (abd + acd + bcd));
}



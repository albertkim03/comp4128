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
        // Standard recipe: hash the two parts and mix them.
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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k;                 // dimensions and #queries
    cin>>n>>m>>k;

    vector<string> g(n);
    for(auto& row:g) cin>>row;             // read the map

    vector<vector<int>> id(n, vector<int>(m, -1));   // -1 = unvisited
    vector<ll> paint;                                // id -> pictures

    static const int dx[4]={-1,1,0,0}, dy[4]={0,0,-1,1};
    auto inside = [&](int x,int y){return 0<=x && x<n && 0<=y && y<m;};

    for(int sx=0;sx<n;++sx)
        for(int sy=0;sy<m;++sy)
            if(g[sx][sy]=='.' && id[sx][sy]==-1){
                queue<pair<int,int>> q;
                q.push({sx,sy});
                id[sx][sy] = paint.size();          // new island number
                ll pics = 0;

                while(!q.empty()){
                    auto [x,y] = q.front(); q.pop();
                    for(int d=0; d<4; ++d){
                        int nx = x + dx[d], ny = y + dy[d];
                        if(!inside(nx,ny) || g[nx][ny]=='*'){ ++pics; continue; }
                        if(id[nx][ny]==-1){
                            id[nx][ny] = id[sx][sy];
                            q.push({nx,ny});
                        }
                    }
                }
                paint.push_back(pics);              // store result
            }


    while(k--){
        int x,y; cin>>x>>y;        // 1-based
        cout << paint[ id[x-1][y-1] ] << '\n';
    }
    return 0;
}
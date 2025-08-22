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


using namespace std;
typedef long long ll;

// const ll INF = (1LL << 61);
const int INF = 1000*1000*1000+7;
const ll MOD = 1000 * 1000 * 1000 + 7;
const int N =200;

const int DISTANCE = 0;
const int X = 1;
const int Y = 2;
const int LAYER = 3;

typedef vector<int> edge;

int main() {
    // freopen("visitfj.in", "r", stdin);
    // freopen("visitfj.out", "w", stdout);


    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // vector <edge> edges[N][N];
    int dist[N][N][3]; 

    int n; cin >> n;
    int t; cin >> t;

    priority_queue <edge , vector <edge>, greater <edge>> pq;


    vector<vector<int>> farm(n, vector<int>(n, 0));

    for (int i = 0; i < pow(n, 2); ++i) {
        int cur_cell; cin >> cur_cell;

        farm[floor(i / n)][i % n] = cur_cell;
    }

    // int layer = 0;

    auto dijkstra = [&](int x, int y) {

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                for (int k = 0; k < 3; ++k)
                    dist[i][j][k] = INF;
        
        pq.push(edge{0, x, y, 0});

        while (!pq.empty()) {
            // layer = (layer + 1) % 3;

            edge cur = pq.top();
            pq.pop();

            int cur_x = cur[X];
            int cur_y = cur[Y];
            int cur_layer = cur[LAYER];
            int d = cur[DISTANCE];


            if (dist[cur_x][cur_y][cur_layer] == INF) {
                dist[cur_x][cur_y][cur_layer] = d;
                
                // adjacency list isn't necessary ebcause we know all neighbours
                // can just be calculated upon visit as top down left irght
                
                
                // top
                if (cur_y - 1 >= 0) {
                    int w = cur_layer != 2 ? t : farm[cur_x][cur_y - 1] + t;

                    pq.push({
                        w + d, 
                        cur_x,
                        cur_y - 1, 
                        (cur_layer + 1) % 3
                    });
                }

                // down
                if (cur_y + 1 <= n - 1) {
                    int w = cur_layer != 2 ? t : farm[cur_x][cur_y + 1] + t;

                    pq.push({
                        w + d, 
                        cur_x,
                        cur_y + 1, 
                        (cur_layer + 1) % 3
                    });
                }

                // right
                if (cur_x + 1 <= n - 1) {
                    int w = cur_layer != 2 ? t : farm[cur_x + 1][cur_y] + t;

                    pq.push({
                        w + d, 
                        cur_x + 1,
                        cur_y, 
                        (cur_layer + 1) % 3
                    });
                }

                // left
                if (cur_x - 1 >= 0) {
                    int w = cur_layer != 2 ? t : farm[cur_x - 1][cur_y] + t;

                    pq.push({
                        w + d, 
                        cur_x - 1,
                        cur_y, 
                        (cur_layer + 1) % 3
                    });
                }
            }

        }
    };

    dijkstra(0, 0);
    
    // cout << dist[n -1][n - 1][0] << "\n";
    // cout << dist[n -1][n - 1][1] << "\n";
    // cout << dist[n -1][n - 1][2] << "\n";
    cout << min(min(dist[n -1][n - 1][0], dist[n -1][n - 1][1]), dist[n -1][n - 1][2]);
    return 0;

}

// g++15 -Wall -std=c++17 -o solution solution.cpp
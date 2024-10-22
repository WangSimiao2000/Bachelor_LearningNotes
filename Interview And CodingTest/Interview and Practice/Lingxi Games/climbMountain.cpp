#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point(int x, int y): x(x), y(y) {}
};

int main() {
    int N, Cd, Cu, Cc;
    cin >> N >> Cd >> Cu >> Cc;
    vector<Point> pos(N);
    for(int i = 0; i < N; i++) {
        cin >> pos[i].x >> pos[i].y;
    }
    vector<int> dp(N, 1e9);
    dp[0] = 0;

    for(int i = 1; i < N; i++) {
        for(int j = 0; j < i; j++) {
            int distance = sqrt(pow(pos[i].x - pos[j].x, 2) + pow(pos[i].y - pos[j].y, 2));

            if(pos[i].y > pos[j].y) {
                //计算点j水平延申到点i与点i+1连线的交点
                double x = pos[j].x + (pos[i].y - pos[j].y) * (pos[i].x - pos[j].x) / (pos[i].y - pos[j].y + 1);
                Point p(x, pos[i].y);
                
            }else{
                dp[i] = min(dp[i], dp[j] + distance * Cd);            
            }
        }
    }
}
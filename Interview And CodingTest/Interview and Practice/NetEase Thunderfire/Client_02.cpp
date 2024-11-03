#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/*
已知有一系列已知坐标的点在平面上，
已知圆的半径，求能覆盖点数量最多的圆心坐标，如果有多个则输出x最大的那个

坐标都是整数(包括圆心坐标)
*/

int main()
{
    int R;
    cin >> R;
    int N;
    cin >> N;
    vector<pair<int, int>> MonstersPos(N);
    for (int i = 0; i < N; i++)
    {
        cin >> MonstersPos[i].first >> MonstersPos[i].second;
    }

    int            max_count   = 0;
    pair<int, int> best_center = {0, 0};

    for (int i = 0; i < N; ++i)
    {
        for(int j = i + 1; j < N; ++j){
            int dx = MonstersPos[j].first - MonstersPos[i].first;
            int dy = MonstersPos[j].second - MonstersPos[i].second;
            int distance_squared = dx * dx + dy * dy;

            if(distance_squared <= (2 * R) * (2 * R)){
                int mid_x = (MonstersPos[i].first + MonstersPos[j].first) / 2;
                int mid_y = (MonstersPos[i].second + MonstersPos[j].second) / 2;

                double d = sqrt(distance_squared);
                if (d > 2 * R)
                {
                    continue;                
                }

                double offset = sqrt(R*R - (d/2) * (d/2));
                int offset_x = static_cast<int>(round((dy / d )* offset));
                int offset_y = static_cast<int>(round((-dx / d) * offset));

                int center1_x = mid_x + offset_x;
                int center1_y = mid_y + offset_y;
                int count1 = 0;

                for (const auto& pos : MonstersPos){
                    int dist_sq = (pos.first - center1_x) * (pos.first - center1_x) + (pos.second - center1_y) * (pos.second - center1_y);
                    if(dist_sq <= R * R){
                        count1++;
                    }
                }

                if(count1 > max_count || (count1 == max_count && center1_x > best_center.first)){
                    max_count = count1;
                    best_center = {center1_x, center1_y};
                }

                int center2_x = mid_x - offset_x;
                int center2_y = mid_y - offset_y;
                int count2 = 0;

                for (const auto& pos : MonstersPos){
                    int dist_sq = (pos.first - center2_x) * (pos.first - center2_x) + (pos.second - center2_y) * (pos.second - center2_y);
                    if(dist_sq <= R * R){
                        count2++;
                    }
                }

                if(count2 > max_count || (count2 == max_count && center2_x > best_center.first)){
                    max_count = count2;
                    best_center = {center2_x, center2_y};
                }
            }
        }
    }

    cout << best_center.first << " " << best_center.second << endl;

    return 0;
}
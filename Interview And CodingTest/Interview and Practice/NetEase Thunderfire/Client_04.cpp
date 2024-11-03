#include <iostream>
// #include <queue>
#include <vector>

using namespace std;

/*
# 采集鲜花比赛最短时间问题

## 问题描述
在一个采集鲜花的比赛中，需要 \( M \) 个玩家组队合作采集鲜花。比赛中有两种鲜花，每种鲜花都需要采集 \( N \) 朵。每位玩家采集两种鲜花的效率不同，每次只能选择采集其中一种鲜花。

给定每个玩家采集两种鲜花所需的时间，求完成任务的最短时间。

## 输入描述
- 第一行包含两个整数 \( M \) 和 \( N \)：
  - \( M \)：玩家的数量。
  - \( N \)：每种鲜花需要采集的数量。
  
- 接下来 \( M \) 行，每行包含两个整数 \( a_i \) 和 \( b_i \)，分别表示第 \( i \) 位玩家采集鲜花1和鲜花2的耗时。

## 输出描述
输出一个整数，表示完成采集任务的最少时间。

## 示例

### 输入
```
3 12
2 3
3 2
4 1
```

### 输出
```
15
```
*/

struct Player {
    int time1;
    int time2;
};

// bool compareByTime(const Player& p1, const Player& p2) {
//     return p1.time1 < p2.time1 || (p1.time1 == p2.time1 && p1.time2 < p2.time2);
// }

// int minTimeToCollectFlowers(vector<Player>& players, int N) {
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
//     int total1 = 0;
//     int total2 = 0;
//     int timeSpent = 0;

//     for(const auto& player : players) {
//         pq.push({player.time1, 1});
//         pq.push({player.time2, 2});
//     }

//     while (total1 < N || total2 < N) {        
//         auto [currentTime, flowerType] = pq.top();
//         pq.pop();

//         timeSpent = currentTime;

//         if(flowerType == 1) {
//             if (total1 < N) {
//                 total1++;
//             } else {
//                 continue;
//             }
//         } else if (flowerType == 2) {
//             if (total2 < N) {
//                 total2++;
//             } else {
//                 continue;            
//             }
//         }

//         if(total1 == N && total2 == N) {
//             break;
//         }
//     }

//     return timeSpent;        
// }

int main() {
    int M,N;
    cin >> M >> N;
    vector<Player> players(M);
    for (int i = 0; i < M; i++) {
        cin >> players[i].time1 >> players[i].time2;
    }

    // int result = minTimeToCollectFlowers(players, N);
    //cout << result << endl;   

    return 0;
}
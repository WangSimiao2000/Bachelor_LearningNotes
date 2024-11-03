#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
# 祖玛游戏轨道珠子消除问题

## 问题描述
给定一个祖玛游戏的轨道珠子状态和一个待发射珠子的队列，每次可以选择在轨道上任意两个相邻珠子中间（包括轨道头和尾）插入一个待发射珠子。插入后，如果轨道上的珠子满足消除条件（即至少有 \( M \) 个相同颜色的珠子连续在一起），则触发消除。消除后如果新的相邻珠子又满足消除条件，则继续消除，直到没有符合消除条件的珠子为止。每消除一颗珠子得一分，要求计算最大可获得的分数。

## 输入描述
- 第一行输入三个整数 \( L_1 \)、\( L_2 \)、\( M \)：
  - \( L_1 \)：轨道上初始珠子列表长度。
  - \( L_2 \)：待发射珠子的个数。
  - \( M \)：在这场祖玛游戏中至少 \( M \) 个相同颜色的珠子连在一起才能触发消除。
  
- 第二行是一个字符串，由大写英文字母表示轨道上的珠子列表，共 \( L_1 \) 个。
- 第三行是一个字符串，由大写英文字母表示待发射珠子的列表，共 \( L_2 \) 个。

> 输入保证轨道上的珠子初始状态不会出现连续 \( M \) 个相同颜色的珠子。

## 输出描述
输出一个整数，表示最大可获得的分数。

## 示例

### 输入
```
7 1 3
ABBCCBA
C
```

### 输出
```
6
```
*/

// M是出现连续M个相同字符时，这些字符会被消除
int eliminate(string& track, int M) {
    int score = 0;
    bool eliminated = true;

    while(eliminated) {
        eliminated = false;
        string newTrack = "";
        int count = 1;
        
        for (int i = 0; i < track.length(); ++i){
            if(i < track.length() - 1 && track[i] == track[i + 1]){
                count++;
            } else {
                // 
                if(count >= M){
                    score += count;
                    eliminated = true;
                } else {
                    newTrack += string(count, track[i]);
                }
                count = 1;
            }
        }
        track = newTrack;
    }

    return score;
}

int maxScore(string track, string& bullets, int index, int M) {
    if (index == bullets.length()){
        return  0;
    }
    
    int maxScoreAchieved = 0;

    for(int i = 0; i < track.length(); ++i){
        string newTrack = track;
        newTrack.insert(i, 1, bullets[index]);

        int score = eliminate(newTrack, M);
        
        maxScoreAchieved = max(maxScoreAchieved, score + maxScore(newTrack, bullets, index + 1, M));
    }
    return maxScoreAchieved;
}

int main(){
    int L1, L2, M;
    cin >> L1 >> L2 >> M;

    string track;
    string bullets;

    cin >> track >> bullets;

    int result = maxScore(track, bullets, 0, M);
    cout << result << endl;

    return 0;
}
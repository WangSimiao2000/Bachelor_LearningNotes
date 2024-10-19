#include <cstddef>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

/*
(未解决)
### 题目描述：

0 代表玩家没有体验过游戏，1 代表体验过，2 代表体验过并投票。

- 至少体验过三款游戏的玩家才能投票；
- 每个玩家最多可以对 5 款游戏投票，如果投票数量超过 5，则该玩家的投票无效；
- 如果玩家体验的游戏数量不足 3 款，则该玩家的投票无效。

程序应输出票数最高的游戏的 ID，如果有多个游戏得票数相同，按游戏 ID 的升序排列，使用空格隔开。

### 输入：
- 第一行输入 `n`，表示玩家的数量。
- 接下来 `n` 行，每行输入 10 个数字，分别表示某个玩家对 10 款游戏的体验和投票情况：
  - `0` 表示玩家未体验该游戏；
  - `1` 表示玩家体验过该游戏；
  - `2` 表示玩家体验过且对该游戏投了票。

### 输出：
输出票数最高的游戏 ID，多个则用空格隔开，小的优先。

### 输入示例：
```
4
0 1 2 1 0 1 0 1 2 0
0 0 1 2 0 0 0 2 0 0
0 1 1 1 1 1 0 2 2 0
0 1 2 1 0 1 0 2 1 0
```

### 输出示例：
```
3 8 9
```

### 说明：
- 玩家 1 投票给了游戏 2 和 8，体验的游戏数量为 6，有效投票。
- 玩家 2 投票给了游戏 3 和 7，体验游戏数量为 3，有效投票。
- 玩家 3 投票给了游戏 7、8 和 9，体验游戏数量为 7，有效投票。
- 玩家 4 投票给了游戏 2、7 和 9，体验游戏数量为 6，有效投票。
  
最终，游戏 3、8 和 9 得票数最高，按升序输出。
*/

int main() {
    int n;
    cin >> n;
    vector<vector<int>> playerData(n, vector<int>(10));
    vector<int> votes(10, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> playerData[i][j];
        }
    }

    for(const auto& player : playerData) {
        int experienceCount = 0;
        int voteCount = 0;
        for (int j = 0; j < 10; j++) {
            if (player[j] >= 1) {
                experienceCount++;
            } 
            if (player[j] == 2) {
                voteCount++;            
            }
        }
        if(experienceCount >= 3 && voteCount <= 5) {
           for(int j = 0; j < 10; j++) {
               if(player[j] == 2) {
                   votes[j]++;
               }
           }
        }
    }

    int maxVotes = *max_element(votes.begin(), votes.end());
    vector<int> result;

    for(int i = 0; i < 10; i++) {
        if(votes[i] == maxVotes) {
            result.push_back(i + 1);//+1 because the index starts from 0
        }
    }

    for(size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if(i != result.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
一个二维数组，每个数字代表该区域滑雪场地高度，一个人可以从某个点滑向上下左右相邻四个点之一，当且仅当高度减小

输入第一行两个数R C表示行数列数
下面是R行，每行C个整数
输出最长滑雪路径经过点的数量
*/

// 定义方向数组，表示上下左右的移动
const vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// 递归函数，计算从当前点的最长滑雪路径
int dfs(int x, int y, vector<vector<int>>& heights, vector<vector<int>>& dp) {
    if (dp[x][y] != -1) {
        return dp[x][y]; // 如果已经计算过，直接返回结果
    }

    dp[x][y] = 1; // 初始化当前点的路径长度为 1（包含自身）
    
    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        // 确保新坐标在边界内，并且高度减小
        if (newX >= 0 && newX < heights.size() && newY >= 0 && newY < heights[0].size() &&
            heights[newX][newY] < heights[x][y]) {
            dp[x][y] = max(dp[x][y], 1 + dfs(newX, newY, heights, dp)); // 更新最长路径
        }
    }

    return dp[x][y]; // 返回当前点的最长路径
}

int main() {
    int R, C;
    cin >> R >> C; // 读取行数和列数

    vector<vector<int>> heights(R, vector<int>(C));
    vector<vector<int>> dp(R, vector<int>(C, -1)); // 初始化记忆化数组

    // 读取高度数据
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cin >> heights[i][j];
        }
    }

    int longestPath = 0; // 存储最长路径长度

    // 遍历每个点，计算最长路径
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            longestPath = max(longestPath, dfs(i, j, heights, dp)); // 更新最长路径
        }
    }

    cout << longestPath << endl; // 输出最长滑雪路径经过点的数量

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
/*
输入
第一行包含4个整数N,M,K,P
表示N点体力M枚金币K处宝藏，宝藏间P处道路
接下来K行每行两个整数value,cost，表示宝藏价值和解锁所需金币
接下来P行每行三个整数abt，表示宝藏a到宝藏b需要花费t点体力

输出一个整数表示可以获取的最大价值
*/

struct Treasure {
    int value; // 宝藏价值
    int cost;  // 解锁所需金币
};

struct Path {
    int to;    // 目标宝藏
    int stamina; // 从a到b所需体力
};

int maxTreasureValue(int N, int M, int K, int P, vector<Treasure>& treasures, vector<Path>& paths) {
    // 邻接表表示宝藏之间的道路
    vector<vector<Path>> graph(K + 1);
    for (const auto& path : paths) {
        graph[path.to].push_back({path.to, path.stamina});
    }

    // DP表：dp[remaining_stamina][remaining_gold]
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, 0));

    // 遍历所有宝藏，更新DP表
    for (int i = 1; i <= K; ++i) {
        int value = treasures[i - 1].value;
        int cost = treasures[i - 1].cost;
        
        // 从后向前更新DP表
        for (int stamina = N; stamina >= 0; --stamina) {
            for (int gold = M; gold >= cost; --gold) {
                dp[stamina][gold] = max(dp[stamina][gold], dp[stamina][gold - cost] + value);
            }
        }
    }

    // 寻找最大价值
    int maxValue = 0;
    for (int stamina = 0; stamina <= N; ++stamina) {
        for (int gold = 0; gold <= M; ++gold) {
            maxValue = max(maxValue, dp[stamina][gold]);
        }
    }

    return maxValue;
}

int main() {
    int N, M, K, P;
    cin >> N >> M >> K >> P;

    vector<Treasure> treasures(K);
    for (int i = 0; i < K; ++i) {
        cin >> treasures[i].value >> treasures[i].cost;
    }

    vector<Path> paths(P);
    for (int i = 0; i < P; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        paths[i] = {b, t}; // 假设输入的 a, b, t 与问题描述一致
    }

    int result = maxTreasureValue(N, M, K, P, treasures, paths);
    cout << result << endl;

    return 0;
}

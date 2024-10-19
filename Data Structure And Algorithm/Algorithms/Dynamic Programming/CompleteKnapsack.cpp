#include <iostream>
#include <vector>

using namespace std;

/*
完全背包问题
给定 n 个物品，第 i 个物品的重量为 wgt[i-1]、价值为 val[i-1] ，和一个容量为 cap 的背包。每个物品可以选择无限次，问在限定背包容量下能放入物品的最大价值
*/

/* 完全背包：动态规划 */
/*
- 在 0-1 背包问题中, 每种物品只有一个, 因此将物品 i 放入背包后, 只能从前 i-1 种物品中选择
- 在完全背包问题中, 每种物品可以选择无限次, 因此将物品 i 放入背包后, 仍然可以从前 i 种物品中选择

在完全背包问题的规定下, 状态[i,c]的变化分为两种情况:
- 不放入物品 i: 与 0-1 背包问题相同, 转移至状态[i-1,c]
- 放入物品 i: 由于物品 i 可以选择无限次, 因此转移至状态[i,c-wgt[i-1]] (即背包容量减去物品 i 的重量)

状态转移方程:
dp[i, c] = max(dp[i-1, c], dp[i, c-wgt[i-1]] + val[i-1])

c: 背包容量
dp[i, c]: 前 i 种物品在背包容量为 c 时的最大价值
*/

/* 完全背包：动态规划 */
int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    // 初始化 dp 表
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                // 若超过背包容量，则不选物品 i
                dp[i][c] = dp[i - 1][c];
            } else {
                // 不选和选物品 i 这两种方案的较大值
                dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* 完全背包：空间优化后的动态规划 */
int unboundedKnapsackDPComp(vector<int> &wgt, vector<int> &val, int cap) {
    int n = wgt.size();
    // 初始化 dp 表
    vector<int> dp(cap + 1, 0);
    // 状态转移
    for (int i = 1; i <= n; i++) {
        for (int c = 1; c <= cap; c++) {
            if (wgt[i - 1] > c) {
                // 若超过背包容量，则不选物品 i
                dp[c] = dp[c];
            } else {
                // 不选和选物品 i 这两种方案的较大值
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

int main() {
    vector<int> wgt = {2, 3, 4, 7};
    vector<int> val = {1, 3, 5, 9};
    int cap = 10;
    cout << unboundedKnapsackDP(wgt, val, cap) << endl;  // Output: 12
    cout << unboundedKnapsackDPComp(wgt, val, cap) << endl;  // Output: 12
    return 0;
}
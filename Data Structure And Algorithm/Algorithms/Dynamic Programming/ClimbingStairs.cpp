#include <iostream>
#include <vector>

using namespace std;

/* 方法1: 回溯 */
void backtrack(vector<int> &choices, int state, int n, vector<int> &res) {
    // 当爬到第 n 阶时, 方案数量加 1
    if (state == n)
        res[0]++;
    // 遍历所有选择
    for (auto &choice : choices) {
        // 剪枝：不允许越过第 n 阶
        if (state + choice > n)
            continue;
        // 尝试：做出选择, 更新状态
        backtrack(choices, state + choice, n, res);
        // 回退
    }
}

/* 爬楼梯：回溯 */
int climbingStairsBacktrack(int n) {
    vector<int> choices = {1, 2}; // 可选择向上爬 1 阶或 2 阶
    int state = 0;                // 从第 0 阶开始爬
    vector<int> res = {0};        // 使用 res[0] 记录方案数量
    backtrack(choices, state, n, res);
    return res[0];
}

/* 方法2: 暴力搜索 */
/* 
设爬到第 n 阶的方案数量为 f(n), 则 f(n) 就是原问题
子问题包括: f(n-1) ,f(n-2), ..., f(2), f(1)

每轮只能上 1 阶或 2 阶, 因此当我们站在第 n 阶楼梯上时, 上一轮只可能站在第 n-1 阶或第 n-2 阶上
换句话说, 我们只能从第 i-1 阶或第 i-2 阶迈向第 i 阶

爬到第 n-1 阶的方案数加上爬到第 n-2 阶的方案数就等于爬到第 n 阶的方案数
即 f(n) = f(n-1) + f(n-2)

以 dp[n] 为起始点, 递归地将一个较大问题拆解为两个较小问题的和, 直至到达最小子问题 dp[1] 和 dp[2] 时返回. 
其中, 最小子问题的解是已知的, 即 dp[1] = 1 和 dp[2] = 2 , 表示爬到第 1 , 2 阶的方案数分别为 1 和 2
*/

int dfs(int i) {
    // 已知 dp[1] 和 dp[2] ，返回之
    if (i == 1 || i == 2)
        return i;
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1) + dfs(i - 2);
    return count;
}

/* 爬楼梯：暴力搜索 */
int climbingStairsDFS(int n) {
    return dfs(n);
}

/* 方法3: 记忆化搜索 */
/*
我们希望所有的重叠子问题都只被计算一次
声明一个数组 mem 来记录每个子问题的解, 并在搜索过程中将重叠的子问题剪枝
1. 当首次计算 dp[i] 时, 将其存储在 mem[i] 中
2. 当重复计算 dp[i] 时, 直接从 mem[i] 中取值
*/

/* 记忆化搜索 */
int dfsMem(int i, vector<int> &mem) {
    // 已知 dp[1] 和 dp[2] ，返回之
    if (i == 1 || i == 2)
        return i;
    // 若存在记录 dp[i] ，则直接返回之
    if (mem[i] != -1)
        return mem[i];
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfsMem(i - 1, mem) + dfsMem(i - 2, mem);
    // 记录 dp[i]
    mem[i] = count;
    return count;
}

/* 爬楼梯：记忆化搜索 */
int climbingStairsDFSMem(int n) {
    // mem[i] 记录爬到第 i 阶的方案总数，-1 代表无记录
    vector<int> mem(n + 1, -1);
    return dfsMem(n, mem);
}

/* 方法4: 动态规划 */
/*
记忆化搜索的递归实现实际上是"自顶向下"的动态规划
动态规划的思路是"自底向上"地计算每个子问题的解

动态规划不包含回溯, 因此只需循环迭代实现, 无须递归
*/

/* 爬楼梯：动态规划 */
int climbingStairsDP(int n) {
    if (n == 1 || n == 2)
        return n;
    // 初始化 dp 表，用于存储子问题的解
    vector<int> dp(n + 1);
    // 初始状态：预设最小子问题的解
    dp[1] = 1;
    dp[2] = 2;
    // 状态转移：从较小子问题逐步求解较大子问题
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/* 爬楼梯：空间优化后的动态规划 */
int climbingStairsDPComp(int n) {
    if (n == 1 || n == 2)
        return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++) {
        // 仅保留最近的两个子问题的解
        // tmp 用于暂存 dp[i-1]，以便计算 dp[i] = dp[i-1] + dp[i-2]
        // a 用于存储 dp[i-2]，b 用于存储 dp[i-1]
        int tmp = b;
        b = a + b;
        a = tmp;
    }
    return b;
}

int main(){
    int n = 5;
    
    // 回溯
    int res1 = climbingStairsBacktrack(n);
    // 暴力搜索
    int res2 = climbingStairsDFS(n);
    // 记忆化搜索
    int res3 = climbingStairsDFSMem(n);
    // 动态规划
    int res4 = climbingStairsDP(n);
    // 空间优化后的动态规划
    int res5 = climbingStairsDPComp(n);

    // 输出结果
    cout << "回溯：" << res1 << endl;
    cout << "暴力搜索：" << res2 << endl;
    cout << "记忆化搜索：" << res3 << endl;
    cout << "动态规划：" << res4 << endl;
    cout << "空间优化后的动态规划：" << res5 << endl;

    return 0;
}
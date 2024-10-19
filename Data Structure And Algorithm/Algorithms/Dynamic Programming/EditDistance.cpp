#include <iostream>
#include <vector>

using namespace std;

/* 
编辑距离问题:
输入两个字符串 s 和 t ，返回将 s 转换为 t 所需的最少编辑步数。
你可以在一个字符串中进行三种编辑操作：插入一个字符、删除一个字符、将字符替换为任意一个字符。
*/

/*
编辑距离问题可以很自然地用决策树模型来解释。
字符串对应树节点，一轮决策（一次编辑操作）对应树的一条边

动态规划思路:
1. 第一步：思考每轮的决策，定义状态，从而得到 dp 表
2. 第二步：找出最优子结构，进而推导出状态转移方程
3. 第三步：确定边界条件和状态转移顺序
*/

/*
第一步：思考每轮的决策，定义状态，从而得到 dp 表:

每一轮决策是对字符串 s 进行一次编辑操作
我们希望: 编辑过程中问题规模逐渐减小, 这样才能构建子问题
设字符串 s 和 t 的长度分别为 n 和 m, 优先考虑两字符串尾部的字符 s[n-1] 和 t[m-1]
- 若 s[n-1] == t[m-1], 我们可以跳过它, 直接考虑 s[n-2] 和 t[m-2]
- 若 s[n-1] != t[m-1], 我们需要对s进行一次编辑 (插入, 删除, 替换), 使得两字符串尾部字符相同

也就是说, 我们在字符串 s 中进行的每一轮决策(编辑操作), 都会使得 s 和 t 中剩余的待匹配字符发生变化
因此, 状态为当前在 s 和 t 中考虑的第 i 个和第 j 个字符, 记为 [i, j]

状态 [i, j] 对应的子问题: 将 s 的前 i 个字符转换为 t 的前 j 个字符所需的最少编辑步数

至此得到一个尺寸为 (i+1) * (j+1) 的二维 dp 表
*/

/*
第二步：找出最优子结构，进而推导出状态转移方程:
考虑子问题 dp[i, j]，其对应的两个字符串尾部字符为 s[i-1] 和 t[j-1], 可以根据不同操作进行分类讨论:
1. 在 s[i-1] 之后添加 t[j-1], 则剩余子问题 dp[i, j-1]
2. 删除 s[i-1], 则剩余子问题为 dp[i-1, j]
3. 将 s[i-1] 替换为 t[j-1], 则剩余子问题为 dp[i-1, j-1]

分析可得: 最优子结构: dp[i,j] 的最少编辑步数为 dp[i-1,j-1], dp[i-1,j], dp[i,j-1] 三者中的最小值, 再加上本次操作的编辑步数 1 , 对应的状态转移方程为:
dp[i, j] = min(dp[i-1, j-1], dp[i-1, j], dp[i, j-1]) + 1

注意: 当 s[i-1] == t[j-1] 时, 无需进行编辑操作, 仅需考虑子问题 dp[i-1, j-1] 即可, 此时状态转移方程为:
dp[i, j] = dp[i-1, j-1]
*/

/*
第三步：确定边界条件和状态转移顺序:
- 当两个字符串为空时, 显然编辑距离为 0, 即 dp[0, 0] = 0
- 当 s 为空, t 不为空时, 编辑距离为 t 的长度, 即 dp[0, j] = j
- 当 t 为空, s 不为空时, 编辑距离为 s 的长度, 即 dp[i, 0] = i

观察状态转移方程, 可以发现 dp[i, j] 的计算依赖于 dp[i-1, j-1], dp[i-1, j], dp[i, j-1], 即左上方、上方和左方的值

因此, 通过两层循环正向遍历整个 dp 表即可
*/

/* 编辑距离：动态规划 */
int editDistanceDP(string s, string t){
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // 状态转移: 首行首列
    for(int i = 1; i <= n; i++){
        dp[i][0] = i;
    }
    for(int j = 1; j <= m; j++){
        dp[0][j] = j;
    }
    // 状态转移: 其余行列
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s[i-1] == t[j-1]){
                // 字符相同，无需编辑
                dp[i][j] = dp[i-1][j-1];
            } else {
                // 字符不同，取三种操作的最小值
                dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
            }
        }
    }
    return dp[n][m];
}

/* 编辑距离：空间优化后的动态规划 */
int editDistanceDPComp(string s, string t) {
    int n = s.length(), m = t.length();
    vector<int> dp(m + 1, 0);
    // 状态转移：首行
    for (int j = 1; j <= m; j++) {
        dp[j] = j;
    }
    // 状态转移：其余行
    for (int i = 1; i <= n; i++) {
        // 状态转移：首列
        int leftup = dp[0]; // 暂存 dp[i-1, j-1]
        dp[0] = i;
        // 状态转移：其余列
        for (int j = 1; j <= m; j++) {
            int temp = dp[j];
            if (s[i - 1] == t[j - 1]) {
                // 若两字符相等，则直接跳过此两字符
                dp[j] = leftup;
            } else {
                // 最少编辑步数 = 插入、删除、替换这三种操作的最少编辑步数 + 1
                dp[j] = min(min(dp[j - 1], dp[j]), leftup) + 1;
            }
            leftup = temp; // 更新为下一轮的 dp[i-1, j-1]
        }
    }
    return dp[m];
}

int main(){
    string s = "kitten";
    string t = "sitting";
    cout << editDistanceDP(s, t) << endl; // 3
    cout << editDistanceDPComp(s, t) << endl; // 3
    return 0;
}
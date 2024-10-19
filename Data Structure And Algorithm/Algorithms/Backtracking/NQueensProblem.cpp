#include <vector>
#include <iostream>

using namespace std;

/*
n 皇后问题:
根据国际象棋的规则, 皇后可以攻击与同处一行, 一列或一条斜线上的棋子. 给定 n 个皇后和一个 n × n 大小的棋盘, 寻找使得所有皇后之间无法相互攻击的摆放方案
- 多个皇后不能在同一行, 同一列, 同一条对角线上
- 对角线分为主对角线 \ 和次对角线 / 两种
*/

/*
1. 逐行放置策略:
- 皇后的数量和棋盘的行数都为 n , 因此我们容易得到一个推论：棋盘每行都允许且只允许放置一个皇后

2. 列与对角线剪枝:
> 列约束(同一列不能有两个皇后):
- 可以利用一个长度为 n 的布尔型数组 cols 记录每一列是否有皇后. 
- 在每次决定放置前, 我们通过 cols 将已有皇后的列进行剪枝, 并在回溯中动态更新 cols 的状态
> 对角线约束(同一对角线不能有两个皇后):
- 设棋盘中某个格子的行列索引为 (row, col), 则可以发现主对角线上的所有格子满足 row - col 为一个定值
- 如果两个格子满足 row1 - col1 = row2 - col2, 则它们一定处在同一条主对角线上
- 次对角线上的所有格子的 row + col 值都为一个定值
> 主对角线 \, 次对角线 /, 列 |:
- 用 diags1 记录每条主对角线上是否有皇后
- 用 diags2 记录每条次对角线上是否有皇后
- 用 cols 记录每一列是否有皇后
*/

/* 
回溯算法：n 皇后 

row: 当前行
n: 棋盘大小
state: 当前棋盘状态
res: 存放所有解
cols: 记录每一列是否有皇后
diags1: 记录每条主对角线上是否有皇后
diags2: 记录每条次对角线上是否有皇后

注意: 
n 维方阵的 row - col 的范围为 [-(n-1), n-1], 因此主对角线的数量为 2n-1
n 维方阵的 row + col 的范围为 [0, 2n-2], 因此次对角线的数量为 2n-1
即 diags1 和 diags2 的大小都为 2n-1
*/
void backtrack(int row, int n, vector<vector<string>> &state, vector<vector<vector<string>>> &res, vector<bool> &cols,
               vector<bool> &diags1, vector<bool> &diags2) {
    // 当放置完所有行时，记录解
    // 行索引是从 0 ~ n-1, 因此当 row == n 时，说明所有行都已放置完毕
    if (row == n) {
        res.push_back(state);
        return;
    }
    // 遍历所有列
    for (int col = 0; col < n; col++) {
        // 计算该格子对应的主对角线和次对角线
        int diag1 = row - col + n - 1; // 主对角线: +n-1 是为了保证 diag1 >= 0, 作为数组索引
        int diag2 = row + col; // 次对角线
        // 剪枝：不允许该格子所在列、主对角线、次对角线上存在皇后
        if (!cols[col] && !diags1[diag1] && !diags2[diag2]) {
            // 尝试：将皇后放置在该格子
            state[row][col] = "Q";
            cols[col] = diags1[diag1] = diags2[diag2] = true;
            // 放置下一行
            backtrack(row + 1, n, state, res, cols, diags1, diags2);
            // 回退：将该格子恢复为空位
            state[row][col] = "#";
            cols[col] = diags1[diag1] = diags2[diag2] = false;
        }
    }
}

/* 求解 n 皇后 */
vector<vector<vector<string>>> nQueens(int n) {
    // 初始化 n*n 大小的棋盘，其中 'Q' 代表皇后，'#' 代表空位
    vector<vector<string>> state(n, vector<string>(n, "#"));
    vector<bool> cols(n, false);           // 记录列是否有皇后
    vector<bool> diags1(2 * n - 1, false); // 记录主对角线上是否有皇后
    vector<bool> diags2(2 * n - 1, false); // 记录次对角线上是否有皇后
    vector<vector<vector<string>>> res;

    backtrack(0, n, state, res, cols, diags1, diags2);

    return res;
}

int main() {
    int n = 5;
    vector<vector<vector<string>>> res = nQueens(n);
    for (int i = 0; i < res.size(); i++) {
        cout << "Solution " << i + 1 << ":" << endl;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cout << res[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
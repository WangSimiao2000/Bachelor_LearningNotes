#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

/*
题目1: 无重复元素的情况:
给定一个正整数数组 nums 和一个目标正整数 target , 请找出所有可能的组合, 使得组合中的元素和等于 target 
- 给定数组无重复元素, 每个元素可以被选取多次. 
- 请以列表形式返回这些组合, 列表中不应包含重复组合.

注意:
1. 输入集合中的元素可以被无限次重复选取
2. 子集不区分元素顺序, 例如 {1,2} 和 {2,1} 视为同一个子集
*/

/*
参考全排列解法:
- 可以把子集的生成过程想象成一系列选择的结果, 并在选择过程中实时更新"元素和", 当元素和等于 target 时, 就将子集记录至结果列表
- 本题集合中的元素可以被无限次选取, 因此无须借助 selected 布尔列表来记录元素是否已被选择
*/

/* 回溯算法: 子集和 I (包含重复子集) */
void backtrackI(vector<int> &state, int target, int total, vector<int> &choices, vector<vector<int>> &res) {
    // 子集和等于 target 时, 记录解
    if (total == target) {
        res.push_back(state);
        return;
    }
    // 遍历所有选择
    for (size_t i = 0; i < choices.size(); i++) {
        // 剪枝: 若子集和超过 target , 则跳过该选择
        if (total + choices[i] > target) {
            continue;
        }
        // 尝试: 做出选择, 更新元素和 total
        // state 记录当前选择了哪些元素
        state.push_back(choices[i]);
        // 进行下一轮选择
        backtrackI(state, target, total + choices[i], choices, res);
        // 回退: 撤销选择, 恢复到之前的状态
        state.pop_back();
    }
}

/* 求解子集和 I (包含重复子集) */
vector<vector<int>> subsetSumINaive(vector<int> &nums, int target) {
    vector<int> state;       // 状态(子集)
    int total = 0;           // 子集和
    vector<vector<int>> res; // 结果列表(子集列表)
    backtrackI(state, target, total, nums, res);
    return res;
}

/*
去除重复子集:

思路1: 直接对结果列表进行去重(不推荐)
- 当数组元素较多, 尤其是当 target 较大时, 搜索过程会产生大量的重复子集
- 比较子集(数组)的异同非常耗时, 需要先排序数组, 再比较数组中每个元素的异同

思路2: 在搜索过程中通过剪枝去除重复子集
- 第一轮选择 a 且第二轮选择 b 时, 会生成包含两个元素的所有子集, 记为 [a, b, ...].
- 之后当第一轮选择 b 时, 则第二轮应该跳过 a, 因为如果选择 a, 则会生子集 [b, a, ...] 与之前的 [a, b, ...] 重复

在搜索过程中, 每一层的选择都是从左到右被逐个尝试的, 因此越靠右的分支被剪掉的越多

总结来看, 给定输入数组 [x1, x2, ..., xn], 设搜索过程中的选择序列为 [x_i1,x_i2,...,x_im],
则该选择序列需要满足 i1 <= i2 <= ... <= im, 不满足该条件的选择序列都会造成重复, 应当剪枝

实现: 
初始化变量 start , 用于指示遍历起始点.
当做出选择 x_i 后, 设定下一轮从索引 i 开始遍历 (这是因为元素可以被无限次选择, 所以可以重复选择 x_i)
这样做就可以让选择序列满足 i1 < i2 < ... < im , 从而保证子集唯一

优化: 
- 在开启搜索前, 先将数组 nums 排序. 在遍历所有选择时, 当子集和超过 target 时直接结束循环, 因为后边的元素更大, 其子集和一定超过 target
- 省去元素和变量 total , 通过在 target 上执行减法来统计元素和, 当 target 等于 0 时记录解
*/

/* 回溯算法: 子集和 II (不包含重复子集) */
void backtrackII(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res) {
    // 子集和等于 target 时, 记录解
    if (target == 0) {
        res.push_back(state);
        return;
    }
    // 遍历所有选择
    // 剪枝二: 从 start 开始遍历, 避免生成重复子集
    for (int i = start; i < choices.size(); i++) {
        // 剪枝一: 若子集和超过 target , 则直接结束循环
        // 这是因为数组已排序, 后边元素更大, 子集和一定超过 target
        if (target - choices[i] < 0) {
            break;
        }
        // 尝试: 做出选择, 更新 target, start
        state.push_back(choices[i]);
        // 进行下一轮选择
        backtrackII(state, target - choices[i], choices, i, res);
        // 回退: 撤销选择, 恢复到之前的状态
        state.pop_back();
    }
}

/* 求解子集和 II (不包含重复子集) */
vector<vector<int>> subsetSumII(vector<int> &nums, int target) {
    vector<int> state;              // 状态(子集)
    sort(nums.begin(), nums.end()); // 对 nums 进行排序
    int start = 0;                  // 遍历起始点
    vector<vector<int>> res;        // 结果列表(子集列表)
    backtrackII(state, target, nums, start, res);
    return res;
}

/*
题目2: 考虑重复元素的情况: 
给定一个正整数数组 nums 和一个目标正整数 target , 请找出所有可能的组合, 使得组合中的元素和等于 target . 
- 给定数组可能包含重复元素, 每个元素只可被选择一次. 
- 以列表形式返回这些组合, 列表中不应包含重复组合. 

注意:
1. 本题的输入数组可能包含重复元素, 例如 [4,4',5] 和 目标元素 9, 则可能出现子集 [4,5] 和 [4',5] , 出现了重复子集 
2. 子集不区分元素顺序, 例如 {1,2} 和 {2,1} 视为同一个子集
*/

/*
限制相等元素在每一轮中只能被选择一次:
由于数组是已经排序的, 因此想等元素相邻
在某轮选择中, 若当前元素与上一个(左边)元素相等, 则说明已经选择过, 此时应该跳过该元素

本题规定每个数组元素只能被选择一次: 
也可以利用 start 来满足约束:
当做出选择 x_i 后, 设定下一轮从索引 i+1 开始向后遍历
这样既能去除重复子集, 也能避免重复选择元素

注意: 
在上一个问题中, 选择 x_i 后, 下一轮从索引 i 开始遍历, 这是因为元素可以被无限次选择
而在本题中, 选择 x_i 后, 下一轮从索引 i+1 开始遍历, 这是因为元素只能被选择一次
*/

/* 回溯算法: 子集和 III */
void backtrackIII(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res) {
    // 子集和等于 target 时, 记录解
    if (target == 0) {
        res.push_back(state);
        return;
    }
    // 遍历所有选择
    // 剪枝二: 从 start 开始遍历, 避免生成重复子集
    // 剪枝三: 从 start 开始遍历, 避免重复选择同一元素
    for (int i = start; i < choices.size(); i++) {
        // 剪枝一: 若子集和超过 target , 则直接结束循环
        // 这是因为数组已排序, 后边元素更大, 子集和一定超过 target
        // 如果有负数元素, 可以不加这个剪枝
        if (target - choices[i] < 0) {
            break;
        }
        // 剪枝四: 如果该元素与左边元素相等, 说明该搜索分支重复, 直接跳过
        if (i > start && choices[i] == choices[i - 1]) {
            continue;
        }
        // 尝试: 做出选择, 更新 target, start
        state.push_back(choices[i]);
        // 进行下一轮选择
        // 这里要对 start 进行更新, 即 i+1, 保证每个元素只能被选择一次
        backtrackIII(state, target - choices[i], choices, i + 1, res);
        // 回退: 撤销选择, 恢复到之前的状态
        state.pop_back();
    }
}

/* 求解子集和 III */
vector<vector<int>> subsetSumIII(vector<int> &nums, int target) {
    vector<int> state;              // 状态（子集）
    sort(nums.begin(), nums.end()); // 对 nums 进行排序
    int start = 0;                  // 遍历起始点
    vector<vector<int>> res;        // 结果列表（子集列表）
    backtrackIII(state, target, nums, start, res);
    return res;
}

int main() {
    // 要求的目标和
    int target = 9;

    // 输入数组无重复元素, 每个元素可以被选择多次, 但是结果中包含重复子集
    vector<int> numsI = { 3, 4, 5};
    vector<vector<int>> resI = subsetSumINaive(numsI, target);
    for (auto &r : resI) {
        for (auto &e : r) {
            cout << e << " ";
        }
        cout << endl;
    }

    cout << endl;

    // 输入数组无重复元素, 每个元素可以被选择多次, 但是结果中不包含重复子集
    vector<int> numsII = { 3, 4, 5};
    vector<vector<int>> resII = subsetSumII(numsII, target);
    for (auto &r : resII) {
        for (auto &e : r) {
            cout << e << " ";
        }
        cout << endl;
    }

    cout << endl;

    // 输入数组有重复元素, 每个元素只能被选择一次
    vector<int> numsIII = { 4, 4, 5};    
    vector<vector<int>> resIII = subsetSumIII(numsIII, target);
    for (auto &r : resIII) {
        for (auto &e : r) {
            cout << e << " ";
        }
        cout << endl;
    }

    return 0;
}
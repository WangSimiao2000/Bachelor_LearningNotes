#include <iostream>
#include <vector>

using namespace std;

/*
从分治角度，我们将搜索区间[i,j]对应的子问题记为f(i,j)。
以原问题f(0,n−1)为起始点，通过以下步骤进行二分查找。
1. 计算搜索区间[i,j]的中点m，根据它排除一半搜索区间。
2. 递归求解规模减小一半的子问题，可能为f(i,m−1)或f(m+1,j)。
3. 循环第 1. 步和第 2. 步，直至找到 target 或区间为空时返回。
*/

/* 二分查找：问题 f(i, j) */
int dfs(vector<int> &nums, int target, int i, int j){
    // 若区间为空，代表无目标元素，则返回 -1
    if (i > j) {
        return -1;
    }
    // 计算中点索引 m
    int m = (i + j) / 2;
    if (nums[m] < target) {
        // 递归子问题 f(m+1, j)
        return dfs(nums, target, m + 1, j);
    } else if (nums[m] > target) {
        // 递归子问题 f(i, m-1)
        return dfs(nums, target, i, m - 1);
    } else {
        // 找到目标元素，返回其索引
        return m;
    }
}

/* 二分查找 */
int binarySearch(vector<int> &nums, int target) {
    int n = nums.size();
    // 求解问题 f(0, n-1)
    return dfs(nums, target, 0, n - 1);
}

int main(){
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int target = 5;
    cout << binarySearch(nums, target) << endl;  // 4
    return 0;
}
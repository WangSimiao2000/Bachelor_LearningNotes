#include <iostream>
#include <vector>

#include "BinarySearchInsertion.cpp"

using namespace std;

/* 二分查找左边界 */
/*
给定一个长度为 n 的有序数组 nums ，其中可能包含重复元素。
请返回数组中最左一个元素 target 的索引。
若数组中不包含该元素，则返回 -1。
*/

/* 二分查找最左一个 target */
int binarySearchLeftEdge(vector<int> &nums, int target) {
    // 等价于查找 target 的插入点
    int i = binarySearchInsertion(nums, target);
    // 未找到 target ，返回 -1
    if (i == nums.size() || nums[i] != target) {
        return -1;
    }
    // 找到 target ，返回索引 i
    return i;
}

/* 二分查找右边界 */
/*
给定一个长度为 n 的有序数组 nums ，其中可能包含重复元素。
请返回数组中最右一个元素 target 的索引。
若数组中不包含该元素，则返回 -1。
*/

/* 二分查找最右一个 target */
int binarySearchRightEdge(vector<int> &nums, int target) {
    // 转化为查找最左一个 target + 1
    int i = binarySearchInsertion(nums, target + 1);
    // j 指向最右一个 target ，i 指向首个大于 target 的元素
    int j = i - 1;
    // 未找到 target ，返回 -1
    if (j == -1 || nums[j] != target) {
        return -1;
    }
    // 找到 target ，返回索引 j
    return j;
}

int main() {
    vector<int> nums = {1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << binarySearchInsertionSimple(nums, 5) << endl; // 4
    cout << binarySearchInsertion(nums, 5) << endl; // 4
    cout << binarySearchLeftEdge(nums, 2) << endl; // 1
    cout << binarySearchRightEdge(nums, 2) << endl; // 3
    return 0;
}
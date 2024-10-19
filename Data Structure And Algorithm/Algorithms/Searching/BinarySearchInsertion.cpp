#include <vector>

using namespace std;

/* 二分查找插入点 */
/*
1. 无重复元素的情况
给定一个长度为 n 的有序数组 nums 和一个元素 target ，数组不存在重复元素。
现将 target 插入数组 nums 中，并保持其有序性。
若数组中已存在元素 target ，则插入到其左方。
请返回插入后 target 在数组中的索引。
*/

int binarySearchInsertionSimple(vector<int> &nums, int target) {
  int i = 0, j = nums.size() - 1;
  while (i <= j) {
    int mid = i + (j - i) / 2;
    if (nums[mid] < target) {
      i = mid + 1;
    } else if (nums[mid] > target) {
      j = mid - 1;
    } else {
      return mid;
    }
  }
  return i;
}

/*
2. 有重复元素的情况
在上一题的基础上，数组中可能存在重复元素, 其余条件不变。
*/

/* 二分查找插入点（存在重复元素） */
int binarySearchInsertion(vector<int> &nums, int target) {
  int i = 0, j = nums.size() - 1; // 初始化双闭区间 [0, n-1]
  while (i <= j) {
    int m = i + (j - i) / 2; // 计算中点索引 m
    if (nums[m] < target) {
      i = m + 1; // target 在区间 [m+1, j] 中
    } else if (nums[m] > target) {
      j = m - 1; // target 在区间 [i, m-1] 中
    } else {
      j = m - 1; // 首个小于 target 的元素在区间 [i, m-1] 中
    }
  }
  // 返回插入点 i
  return i;
}
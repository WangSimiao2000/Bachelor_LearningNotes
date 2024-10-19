#include <iostream>
#include <vector>

using namespace std;

/* 二分查找 */
/*
给定一个长度为 n 的有序数组 nums 和一个元素 target ，数组不存在重复元素。
现将 target 插入数组 nums 中，并保持其有序性。
若数组中已存在元素 target，则插入到其左方。
请返回插入后 target 在数组中的索引。
*/

int binarySearch(vector<int> &nums, int target) {
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
  return -1;
}

int main() {
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << binarySearch(nums, 5) << endl; // 4
  return 0;
}
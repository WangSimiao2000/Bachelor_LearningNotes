#include <functional>
#include <queue>
#include <stdint.h>
#include <vector>
#include <iostream>

using namespace std;

/*
Top-k问题:
给定一个长度为 n 的无序数组 nums , 请返回数组中最大的 k 个元素
*/

/*
方法1: 遍历选择
- k轮遍历
- 每一轮中提取第 1, 2, ..., k 大的元素
- 只使用与k << n的情况
*/

/*
方法2: 排序
- 先对数组 nums 进行排序
- 再返回右边的 k 个元素
*/

/*
方法3: 堆
1. 初始化一个小顶堆, 堆顶元素最小
2. 将数组前k个元素依次入堆
3. 从第 k + 1个元素开始, 若当前元素大于堆顶元素, 则将堆顶元素出堆, 当前元素入堆
4. 遍历完成即可得到最大k个元素
*/

priority_queue<int, vector<int>, greater<int>> topKHeap(vector<int> &nums, int k){
    // 初始化小顶堆
    priority_queue<int, vector<int>, greater<int>> heap;
    // 将前k个元素入堆
    for(int i = 0; i < k; ++i){
        heap.push(nums[i]);
    }
    // 从第 k+1 个元素开始, 保持堆的长度为 k
    for(int i = k; i < nums.size(); ++i){
        if (nums[i] > heap.top()) {
            heap.pop();
            heap.push(nums[i]);
        }
    }
    return heap;
}

int main(){
    vector<int> nums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    int k = 4;

    priority_queue<int, vector<int>, greater<int>> res = topKHeap(nums, k);

    // 输出
    while (!res.empty()) {
        cout << res.top() << " ";
        res.pop();
    }

    return 0;
}
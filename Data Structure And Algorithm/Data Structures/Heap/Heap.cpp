#include <functional>
#include <queue>
#include <vector>

using namespace std;

/* 堆 */
/*
堆是完全二叉树，可以分为大顶堆和小顶堆
- 最底层节点全部靠左排列, 其他层的节点都被填满
- 二叉树的根节点是"堆顶", 最底层靠右的节点是"堆底"
- 大顶堆: 每个根节点的值都大于等于其子节点的值
- 小顶堆: 每个根节点的值都小于等于其子节点的值
*/

int main(){
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小顶堆
    priority_queue<int, vector<int>, less<int>> maxHeap; // 大顶堆

    // 入堆
    maxHeap.push(1);
    maxHeap.push(3);
    maxHeap.push(2);
    maxHeap.push(5);
    maxHeap.push(4);

    int peek = maxHeap.top(); // 获取堆顶元素

    // 出堆
    maxHeap.pop(); // 5
    maxHeap.pop(); // 4
    maxHeap.pop(); // 3
    maxHeap.pop(); // 2
    maxHeap.pop(); // 1

    int size = maxHeap.size(); // 获取堆大小
    bool isEmpty = maxHeap.empty(); // 判断堆是否为空

    // 根据数组初始化小顶堆
    vector<int> nums = {1, 3, 2, 5, 4};
    priority_queue<int, vector<int>, greater<int>> minHeap2(nums.begin(), nums.end()); // 小顶堆

    return 0;
}
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

class MyMaxHeap {
    private:
        vector<int> maxHeap;

        // 堆的左子节点索引
        int left(int i){return 2 * i + 1;}

        // 堆的右子节点索引
        int right(int i){return 2 * i + 2;}

        // 堆的父节点索引
        int parent(int i){return (i - 1) / 2;}

        // 堆化(从堆底向堆顶) ↑ : 参数i表示从哪个节点开始堆化
        void siftUp(int i){
            while (true) {
                // 获取节点i的父节点索引
                int p = parent(i);
                // 当"越过根节点(堆顶)"或"节点无需修复(父节点大于等于子节点)"时, 退出循环
                if(p < 0 || maxHeap[p] >= maxHeap[i]){
                    break;
                }
                // 交换节点i和其父节点的值
                swap(maxHeap[i], maxHeap[p]);
                // 节点i指向其父节点
                i = p;
            }
        }    

        // 堆化(从堆顶向堆底) ↓ : 参数i表示从哪个节点开始堆化
        void siftDown(int i){
            while(true){
                // 判断节点i及左右节点l和r中的最大值
                int l = left(i), r = right(i), maxIndex = i;
                if(l < maxHeap.size() && maxHeap[l] > maxHeap[maxIndex]){
                    maxIndex = l;
                }
                if(r < maxHeap.size() && maxHeap[r] > maxHeap[maxIndex]){
                    maxIndex = r;
                }
                // 当"节点无需修复(父节点大于等于子节点)"或"节点到达堆底"时, 退出循环
                if(maxIndex == i){
                    break;
                }
                // 交换节点i和其左右节点中的最大值
                swap(maxHeap[i], maxHeap[maxIndex]);
                // 节点i指向其左右节点中的最大值
                i = maxIndex;
            }
        }

    public:

        // 构造方法: 根据输入链表初始化堆
        MyMaxHeap(vector<int> nums){
            // 将数组元素插入堆中
            maxHeap = nums;
            // 堆化: 除叶节点外的所有节点都需要堆化
            // 不需要堆化叶节点, 因为叶节点没有子节点, siftDown会直接退出
            for(int i = parent(maxHeap.size() - 1); i >= 0; i--){
                siftDown(i);
            }
        }

        // 访问堆顶元素
        int peek(){return maxHeap[0];}

        /* 入堆
        1. 将元素插入到堆底
        2. 修复从插入节点到堆顶的路径上的所有节点(堆化)
        堆化: 
        - 依次比较该节点与其父节点的大小,
        - 若父节点小于该节点, 则交换两者的值
        - 直到父节点大于等于该节点, 或者到达堆顶
        */
        void push(int val){
            maxHeap.push_back(val);
            siftUp(maxHeap.size() - 1);
        }

        /* 出堆
        1. 将堆顶元素与堆底元素交换
        2. 删除堆底元素(事实上删除的是原堆顶元素)
        3. 修复从堆顶到堆底的路径上的所有节点(堆化)
        堆化:
        - 依次比较该节点与其左右子节点的大小, 找出最大值
        - 将最大值节点与该节点交换
        - 直到节点大于等于左右子节点, 或者到达堆底
        */
        void pop(){
            // 判空, 抛出异常
            if (maxHeap.empty()) {
                throw out_of_range("Heap is empty");
            }
            // 交换堆顶元素和堆底元素(根节点和最后一个节点)
            swap(maxHeap[0], maxHeap[maxHeap.size() - 1]);
            maxHeap.pop_back();
            // 从堆顶开始堆化
            siftDown(0);
        }
};

int main(){
    vector<int> vec{9,8,6,6,7,5,2,1,4,3,6,2};
    MyMaxHeap maxHeap(vec);

    int peek = maxHeap.peek();
    cout << "peek: " << peek << endl;

    int val = 7;
    maxHeap.push(val);
    cout << "push: " << val << endl;

    maxHeap.pop();
    peek = maxHeap.peek();
    cout << "peek: " << peek << endl;

    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Selection Sort 选择排序
// Time Complexity: O(n^2)
// Space Complexity: O(1)
void selectionSort(vector<int> &nums){
    int n = nums.size();
    // unsorted array: nums[i, n-1]
    // 外循环：未排序区间为 [i, n-1]
    for (int i = 0; i < n - 1; i++) {
        // find the minimum element in unsorted array
        // 内循环：找到未排序区间内的最小元素
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (nums[j] < nums[k]) {
                k = j; // 记录最小元素的索引
            }
        }
        // swap the minimum element with the first element in unsorted array
        // 将该最小元素与未排序区间的首个元素交换
        swap(nums[i], nums[k]);
    }
}

// Bubble Sort 冒泡排序
// Time Complexity: O(n^2)
// Space Complexity: O(1)
void bubbleSort(vector<int> &nums){
    int n = nums.size();
    // unsorted array: nums[0, i]
    // 外循环：未排序区间为 [0, i]
    for(int i = n; i > 0; i--){
        // put the maximum element in unsorted array to its right position
        // 内循环：将未排序区间 [0, i] 中的最大元素交换至该区间的最右端
        for(int j = 0; j < i; j++){
            if(nums[j] > nums[j + 1]){
                // swap the adjacent elements
                // 交换 nums[j] 与 nums[j + 1]
                // 这里使用了 std::swap() 函数
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

// Bubble Sort (Flag Optimization) 冒泡排序(标志优化)
void bubbleSortFlag(vector<int> &nums){
    int n = nums.size();
    // unsorted array: nums[0, i]
    // 外循环：未排序区间为 [0, i]
    for(int i = n; i > 0; i--){
        bool flag = false;
        // put the maximum element in unsorted array to its right position
        // 内循环：将未排序区间 [0, i] 中的最大元素交换至该区间的最右端
        for(int j = 0; j < i; j++){
            if(nums[j] > nums[j + 1]){
                // swap the adjacent elements
                // 交换 nums[j] 与 nums[j + 1]
                // 这里使用了 std::swap() 函数
                swap(nums[j], nums[j + 1]);
                flag = true; // 记录交换元素
            }
        }
        if(!flag){
            break; // 此轮“冒泡”未交换任何元素，直接跳出
        }
    }
}

// Insertion Sort 插入排序
// Time Complexity: O(n^2)
// Space Complexity: O(1)
void insertionSort(vector<int> &nums){
    int n = nums.size();
    // unsorted array: nums[1, n]
    // sorted array: nums[0, i-1]
    // 外循环：已排序区间为 [0, i-1]
    for (int i = 1; i < n; i++) {
        int base = nums[i], j = i - 1;
        // 内循环：将 base 插入到已排序区间 [0, i-1] 中的正确位置
        while (j >= 0 && nums[j] > base) {
            nums[j + 1] = nums[j]; // 将 nums[j] 向右移动一位
            j--;
        }
        nums[j + 1] = base; // 将 base 赋值到正确位置
    }
}

// Quick Sort 快速排序
// Time Complexity: O(nlogn)
// Space Complexity: O(n)
int partition(vector<int> &nums, int left, int right){
    // choose nums[left] as pivot element
    // 以 nums[left] 为基准数
    int i = left, j = right;
    while(i < j){
        while(i < j && nums[j] >= nums[left]){
            // from right to left, find the first element less than pivot
            // 从右向左找首个小于基准数的元素
            j--;
        }
        while(i < j && nums[i] <= nums[left]){
            // from left to right, find the first element greater than pivot
            // 从左向右找首个大于基准数的元素
            i++;
        }
        // swap nums[i] and nums[j]
        // 交换这两个元素
        swap(nums[i], nums[j]);
    }
    // 将基准数交换至两子数组的分界线
    // swap pivot element with two subarrays' boundary
    swap(nums[i], nums[left]);
    // return the index of pivot element
    // 返回基准数的索引
    return i; 
}
void quickSort(vector<int> &nums, int left, int right){
    // if the length of subarray is 1, return
    // 子数组长度为 1 时终止递归
    if(left >= right){
        return;
    }
    // partition the array into two subarrays
    // 哨兵划分
    int pivot = partition(nums, left, right);
    // recursively sort two subarrays
    // 递归排序左右两个子数组
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

// Merge Sort 归并排序
// Time Complexity: O(nlogn)
// Space Complexity: O(n)
void merge(vector<int> &nums, int left, int mid, int right){
    // left subarray: nums[left, mid]
    // right subarray: nums[mid+1, right]
    // 左子数组区间为 [left, mid], 右子数组区间为 [mid+1, right]
    // create a temporary array to store the merged array
    // 创建一个临时数组 tmp ，用于存放合并后的结果
    vector<int> temp(right - left + 1);
    // initialize the index of left subarray and right subarray
    // 初始化左子数组和右子数组的起始索引
    int i = left, j = mid + 1, k = 0;
    // when both subarrays have elements, do comparison and put the smaller one into temp array
    // 当左右子数组都还有元素时，进行比较并将较小的元素复制到临时数组中
    while(i <= mid && j <= right){
        if(nums[i] <= nums[j]){
            temp[k++] = nums[i++]; // 这里是先赋值，再自增, 如果是++i, 则是先自增，再赋值
        }else{
            temp[k++] = nums[j++];
        }
    }
    // put the remaining elements into temp array
    // 将左子数组和右子数组的剩余元素复制到临时数组中
    while (i <= mid) {
        temp[k++] = nums[i++];    
    }
    while (j <= right) {
        temp[k++] = nums[j++];
    }
    // copy the elements in temp array to original array (nums)
    // 将临时数组 tmp 中的元素复制回原数组 nums 的对应区间
    for (int k = 0; k < temp.size(); k++) {
        nums[left + k] = temp[k];
    }
}
void mergeSort(vector<int> &nums, int left, int right){
    // stop condition
    // 递归终止条件
    if(left >= right){
        return;
    }

    // partition stage
    // 划分阶段
    // compute the middle index
    // 计算中间索引
    int mid = left + (right - left) / 2; 
    // sort left subarray
    // 排序左子数组
    mergeSort(nums, left, mid); 
    // sort right subarray
    // 排序右子数组
    mergeSort(nums, mid + 1, right); 

    // merge stage
    // 合并阶段
    merge(nums, left, mid, right);
}

// Heap Sort 堆排序
// Time Complexity: O(nlogn)
// Space Complexity: O(1)
void siftDown(vector<int> &nums, int n, int i){ 
    // n: the length of heap, i: the index of root
    while (true) {
        // judge i,l,r which is the largest, mark the largest index as maxIdx
        // 判断节点 i, l, r 中值最大的节点，记为 maxIdx
        int l = 2 * i + 1; // left child
        int r = 2 * i + 2; // right child
        int maxIdx = i;
        if (l < n && nums[l] > nums[maxIdx]) {
            maxIdx = l;
        }
        if (r < n && nums[r] > nums[maxIdx]) {
            maxIdx = r;
        }
        // if the root is the largest or l, r has exceeded the boundary, break
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (maxIdx == i) {
            break;
        }
        // swap the root with the largest element
        // 交换两节点
        swap(nums[i], nums[maxIdx]);
        // update the index of root
        // 堆向下堆化
        i = maxIdx;
    }
}
void heapSort(vector<int> &nums){
    // build heap:
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for (int i = nums.size() / 2 - 1; i >= 0; i--) {
        siftDown(nums, nums.size(), i);
    }
    // get the maximum element from the heap
    // 从堆中提取最大元素，循环 n-1 轮
    for (int i = nums.size() - 1; i > 0; i--) {
        // swap the root element with the rightmost element (swap the first element with the last element)
        // 交换根节点与最右叶节点(交换首元素与尾元素)
        swap(nums[0], nums[i]);
        // rebuild the heap
        // 以根节点为起点，从顶至底进行堆化
        siftDown(nums, i, 0);
    }
}

// Bucket Sort 桶排序
// Time Complexity: O(n + k)
// Space Complexity: O(n + k)
void bucketSort(vector<float> &nums){
    // initialize k = n/2 buckets, each bucket may contain 2 elements
    // 初始化 k = n/2 个桶，预期向每个桶分配 2 个元素
    int k = nums.size() / 2;
    vector<vector<float>> buckets(k);
    // 1. put elements into buckets
    // 1. 将数组元素分配到各个桶中
    for (float num : nums) {
        // 输入数据范围为 [0, 1)，使用 num * k 映射到索引范围 [0, k-1]
        int index = num * k;
        // 将 num 添加进桶 bucket_idx
        buckets[index].push_back(num);    
    }
    // 2. sort each bucket
    // 2. 对各个桶执行排序
    for (int i = 0; i < k; i++) {
        // 使用内置排序函数，也可以替换成其他排序算法
        sort(buckets[i].begin(), buckets[i].end());
    }
    // 3. merge all buckets
    // 3. 遍历桶合并结果
    int index = 0;
    for (vector<float>  &bucket : buckets) {
        for (float num : bucket) {
            nums[index++] = num;
        }    
    }
}

// Counting Sort 计数排序
// Time Complexity: O(n + m)
// Space Complexity: O(n + m)
/* Naive version: can not sort objects */ 
/* 简单实现，无法用于排序对象 */
void countingSortNaive(vector<int> &nums){
    // 1. find the maximum element m in nums
    // 1. 统计数组最大元素 m
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // 2. count the frequency of each element
    // 2. 统计各数字的出现次数
    // counter[num] represents the frequency of num
    // counter[num] 代表 num 的出现次数
    vector<int> counter(m + 1, 0);
    for (int num : nums) {
        counter[num]++;
    }
    // 3. ergodic counter, put the elements back to nums
    // 3. 遍历 counter ，将各元素填入原数组 nums
    int i = 0;
    for (int num = 0; num <= m; num++) {
        for (int j = 0; j < counter[num]; j++, i++) {
            nums[i] = num;
        }
    }
}
/* Complete version: can sort objects, and is stable sorting */ 
/* 完整实现，可排序对象，并且是稳定排序 */
void countingSort(vector<int> &nums) {
    // 1. find the maximum element m in nums
    // 1. 统计数组最大元素 m
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // 2. count the frequency of each element
    // 2. 统计各数字的出现次数
    // counter[num] represents the frequency of num
    // counter[num] 代表 num 的出现次数
    vector<int> counter(m + 1, 0);
    for (int num : nums) {
        counter[num]++;
    }
    // 3. calculate the prefix sum of counter
    // 3. 求 counter 的前缀和，将“出现次数”转换为“尾索引”
    // 即 counter[num]-1 是 num 在 res 中最后一次出现的索引
    for (int i = 1; i <= m; i++) {
        counter[i] += counter[i - 1];
    }
    // 4. reverse traversal nums, put the elements into the result array "res"
    // 4. 倒序遍历 nums ，将各元素填入结果数组 res
    // initialize the result array "res"
    // 初始化数组 res 用于记录结果
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
        int num = nums[i];
        // put num into the correct index position
        // 将 num 放置到对应索引处
        res[counter[num] - 1] = num;
        // update the frequency of num
        // 令前缀和自减 1 ，得到下次放置 num 的索引
        counter[num]--; 
    }
    // copy the result array "res" to original array "nums"
    // 使用结果数组 res 覆盖原数组 nums
    nums = res; 
}

// Radix Sort 基数排序
// Time Complexity: O(n * k)
// Space Complexity: O(n + d)
/* get the k-th digit of num, exp = 10^(k - 1) */
/* 获取元素 num 的第 k 位，其中 exp = 10^(k-1) */
int digit(int num, int exp){
    // passed in exp to avoid repeated calculation
    // 传入 exp 而非 k 可以避免在此重复执行昂贵的次方计算
    return (num / exp) % 10;
}
/* counting sort for each digit (depends on the k-th digit of each element) */
/* 计数排序（根据 nums 第 k 位排序） */
void countingSortDigit(vector<int> &nums, int exp){
    // 0~9, 10 digits
    // 十进制的位范围为 0~9 ，因此需要长度为 10 的桶数组
    vector<int> counter(10, 0);
    int n = nums.size();
    // count the frequency of each digit
    // 统计 0~9 各数字的出现次数
    for (int i = 0; i < n; i++) {
        counter[digit(nums[i], exp)]++;
    }
    // calculate the prefix sum of counter
    // 求前缀和，将“出现个数”转换为“数组索引”
    for (int i = 1; i < 10; i++) {
        counter[i] += counter[i - 1];
    }
    // reverse traversal nums, put the elements into the result array "res"
    // 倒序遍历，根据桶内统计结果，将各元素填入 res
    vector<int> res(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        int d = digit(nums[i], exp); 
        res[counter[d] - 1] = nums[i]; // 获取 d 在数组中的索引 j, 将当前元素填入索引 j
        counter[d]--; // 将 d 的数量减 1
    }
    // res -> nums
    // 使用结果覆盖原数组 nums
    for (int i = 0; i < n; i++) {
        nums[i] = res[i];
    }
}
/* radix sort */
/* 基数排序 */
void radixSort(vector<int> &nums){
    // find the maximum element m in nums
    // 获取数组的最大元素，用于判断最大位数
    int m = 0;
    for (int num : nums) {
        m = max(m, num);
    }
    // traverse each digit of the maximum element m
    // 按照从低位到高位的顺序遍历
    for (int exp = 1; m / exp > 0; exp *= 10) {
        // 对数组元素的第 k 位执行计数排序
        // k = 1 -> exp = 1
        // k = 2 -> exp = 10
        // 即 exp = 10^(k-1)
        countingSortDigit(nums, exp);
    }
}

int main() {    
    // test for integer type
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    
    // test for float type
    //vector<float> nums = {0.3, 0.1, 0.4, 0.1, 0.5, 0.9, 0.2, 0.6, 0.5, 0.3};

    //selectionSort(nums);
    //bubbleSort(nums);
    //bubbleSortFlag(nums);
    //insertionSort(nums);
    //quickSort(nums, 0, nums.size() - 1);
    //mergeSort(nums, 0, nums.size() - 1);
    //heapSort(nums);
    //bucketSort(nums);
    //countingSortNaive(nums);
    //countingSort(nums);
    radixSort(nums);

    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}
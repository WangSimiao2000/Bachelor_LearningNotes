#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
分数背包问题:
给定 n 种物品, 第 i 种物品的重量为 wgt[i-1], 价值为 val[i-1], 背包容量为 cap, 每种物品只能选择一次, 但可以选择物品的一部分, 价值根据选择的重量比例变化, 问在限定背包容量下能放入物品的最大价值
*/

/*
与 0-1 背包问题相似, 目标是在限定背包容量下放入物品的最大价值, 不同点在于, 我们可以对物品任意地进行切分, 并按照重量比例来计算相应价值
1. 对于物品 i , 它在单位重量下的价值为 val[i-1] / wgt[i-1] , 简称单位价值
2. 假设点放入一部分物品 i, 重量为 w, 则背包增加的价值为 w * (val[i-1] / wgt[i-1])
*/

/*
最大化背包内物品总价值，本质上是最大化单位重量下的物品价值。由此便可推理出贪心策略: 
1. 将物品按照单位价值从高到低进行排序。
2. 遍历所有物品，每轮贪心地选择单位价值最高的物品。
3. 若剩余背包容量不足，则使用当前物品的一部分填满背包
*/

/* 物品 */
class Item {
  public:
    int w; // 物品重量
    int v; // 物品价值

    Item(int w, int v) : w(w), v(v) {
    }
};

/* 分数背包：贪心 */
double fractionalKnapsack(vector<int> &wgt, vector<int> &val, int cap) {
    // 创建物品列表，包含两个属性：重量、价值
    vector<Item> items;
    for (int i = 0; i < wgt.size(); i++) {
        items.push_back(Item(wgt[i], val[i]));
    }
    // 按照单位价值 item.v / item.w 从高到低进行排序
    sort(items.begin(), items.end(), [](Item &a, Item &b) { return (double)a.v / a.w > (double)b.v / b.w; });
    // 循环贪心选择
    double res = 0;
    for (auto &item : items) {
        if (item.w <= cap) {
            // 若剩余容量充足，则将当前物品整个装进背包
            res += item.v;
            cap -= item.w;
        } else {
            // 若剩余容量不足，则将当前物品的一部分装进背包
            res += (double)item.v / item.w * cap;
            // 已无剩余容量，因此跳出循环
            break;
        }
    }
    return res;
}

int main() {
    vector<int> wgt = {10, 20, 30};
    vector<int> val = {60, 100, 120};
    int cap = 50;
    cout << fractionalKnapsack(wgt, val, cap) << endl;
    return 0;
}
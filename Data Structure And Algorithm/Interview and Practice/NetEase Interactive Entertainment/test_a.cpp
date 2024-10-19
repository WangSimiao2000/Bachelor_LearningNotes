#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
(未解决)
### 题目描述：
已知三个vector，分别存储第i个道具的成本，价格，售卖数量限制，k代表售卖总数量限制，求最大利润

### 输入：
- 第一行输入一个整数 `n`，表示道具数量, `k` 表示售卖总数量限制。
- 接下来 `n` 行，每行三个整数 `ci, pi, li`，表示第 `i` 个道具的成本、价格和售卖数量限制。

### 输出：
输出一个整数，表示最大利润。
*/

struct Item {
    long long profit;
    int limit;
};

bool cmp(const Item& a, const Item& b) {
    return a.profit > b.profit;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    // 成本
    vector<int> cost(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> cost[i];
    }
    // 价格
    vector<int> price(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    // 售卖数量限制
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].limit;
        items[i].profit = price[i] - cost[i];
        if (items[i].profit < 0) {
            items[i].limit = 0;
        }
    }
    sort(items.begin(), items.end(), cmp); // 按照利润降序排序

    long long maxProfit = 0;
    for (int i = 0; i < n && k > 0; i++) {
        if(items[i].limit > 0){
            int sellQuantity = min((int)k, items[i].limit);
            maxProfit += sellQuantity * items[i].profit;
            k -= sellQuantity;
            items[i].limit -= sellQuantity;
        }
    }

    cout << maxProfit << endl;

    return 0;
}
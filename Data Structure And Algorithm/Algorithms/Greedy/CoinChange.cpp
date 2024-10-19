#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
给定 n 种硬币, 第 i 种硬币的面值为 coins[i-1], 目标金额为 amt, 每种硬币可以重复选取, 问能够凑出目标金额的最少硬币数量。如果无法凑出目标金额，则返回 -1 
*/

/* 零钱兑换: 贪心 */
int coinChangeGreedy(vector<int> &coins, int amt) {
    // 假设 coins 列表有序
    int i = coins.size() - 1;
    int count = 0;
    // 循环进行贪心选择, 直到无剩余金额
    while (amt > 0){
        // 找到小于且最接近剩余金额的硬币
        while(i > 0 && coins[i] > amt){
            i--;
        }
        amt -= coins[i];
        count++;
    }
    // 若未找到可行方案, 返回 -1
    if(amt == 0){
        return count;
    }
    else {
        return -1;
    }
    // 可以写成一行: return (amt == 0) ? count : -1;
}

int main(){
    vector<int> coins = {1, 2, 5};
    // 对 coins 进行排序
    sort(coins.begin(), coins.end());
    int amt = 11;
    cout << coinChangeGreedy(coins, amt) << endl;
    return 0;
}
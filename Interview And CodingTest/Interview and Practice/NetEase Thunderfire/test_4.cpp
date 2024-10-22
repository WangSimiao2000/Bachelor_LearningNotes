#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

/*
(未解决)
### 题目描述：

场景中有 `n` 只小怪物，它们的角度位置是均匀随机分布的，玩家可以同时对最多 `m` 只小怪物发射箭矢。每只小怪物只能被选中一次。你需要通过选择小怪物，使技能伤害最大化。

伤害系数 `k` 取决于发射箭矢时最近的两只小怪物的角度差。当发射的箭矢不足两只时，`k=180`。实际发射的箭矢数量为 `a`，每支箭矢的伤害公式为：

\[
d = \left( \frac{1}{2m} \right) + \left( \frac{1}{2a} \right) - \left( \frac{180 - k}{360ma} \right)
\]

总伤害为发射的箭矢数量乘以每支箭矢的伤害。如果存在多种情况下总伤害相同，输出箭矢最多的方案。

### 输入：
- 第一行两个整数 `n` 和 `m`，表示小怪物数量和最多可以选择的小怪物数量。
- 接下来 `n` 行，每行一个浮点数 `ai`，表示第 `i` 只小怪物的角度（以度为单位）。

### 输出：
- 第一行输出最大伤害时的角度差 `k`（保留5位小数）。
- 第二行输出最大伤害时实际发射的箭矢数量 `a`。

### 输入示例：
```
10 5
30
35
45
90
130
259
260
289
300
352
```

### 输出示例：
```
41.00000
5
```
*/

double angle_difference(double a, double b){
    double diff = fabs(a - b);
    return min(diff, 360 - diff);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<double> entityAngle(n);
    for(int i = 0; i < n; i++){
        cin >> entityAngle[i];
    }

    // 排序
    sort(entityAngle.begin(), entityAngle.end());
    
    double maxDamage = -1;
    double best_k = 0; 
    int best_a = 0; 

    // 箭矢数量
    for(int a = 2; a <= m; a++){
        double min_diff = 180;

        // 找最小的角度差
        for(int i = 0; i < n; i++){
            // for(int j = i + 1; j < i + a - 1 && j < n; j++){
            //     double diff = entityAngle[j] - entityAngle[i];
            //     if (diff > 0 && diff < min_diff){
            //         min_diff = min(min_diff, diff);                
            //     }
            // }
            int j = (i+a - 1) % n;
            double diff = angle_difference(entityAngle[j], entityAngle[i]);
            min_diff = min(min_diff, diff);
        }

        // a 下的伤害
        double damage =  a * ((1.0 / (2 * m)) + (1.0 / (2 * a)) - (180.0 - min_diff) / (360.0 * m * a));

        if (damage > maxDamage){
            maxDamage = damage;
            best_k = min_diff;
            best_a = a;
        }else if (fabs(damage - maxDamage) < 1e-4 && a > best_a){
            best_k = min_diff;
            best_a = a;        
        }
        // 输出best_k保留5位小数
        cout << fixed << setprecision(5) << best_k << endl;
        cout << best_a << endl;

        return 0;
    }
}
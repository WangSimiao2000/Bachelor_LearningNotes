#include <iostream>
#include <utility>
#include <vector>

using namespace std;


/*
(未解决)
题目描述：

有一个 \(n \times m\) 的矩阵，矩阵第 \(i\) 行第 \(j\) 列的元素编号为 \((i-1) \times m + j\)。

你需要执行以下几种操作：

1. **操作 1**：将第 \(x\) 行与第 \(y\) 行的元素交换。
2. **操作 2**：将第 \(x\) 行的元素向左移动 \(y\) 格，左边多出来的元素按照原顺序补到右边。
3. **操作 3**：查询当前矩阵中第 \(x\) 行第 \(y\) 列的元素编号。

输入格式：
- 第一行包含三个整数 \(n\)、\(m\)、\(q\)，分别表示矩阵的行数、列数和操作次数。
- 接下来的 \(q\) 行中，每行首先包含一个整数 \(t\) 表示操作类别，随后跟着操作所需的参数 \(x\) 和 \(y\)。

输出格式：
- 对于每个操作 3，输出矩阵中第 \(x\) 行第 \(y\) 列的元素编号。

输入示例：
```
2 3 4
1 1 2
3 1 3
2 1 4
3 1 3
```

输出示例：
```
6
4
```
*/

long n, m, q;
vector<vector<int>> matrix;

void doFunc1(long x, long y){
    x--;
    y--;
    swap(matrix[x], matrix[y]);
}

void doFunc2(long x, long y){
    x--;
    y = y % m;
    vector<int> temp_row(m);
    for(int i = 0; i < m; i++){
        temp_row[i] = matrix[x][(i+y)%m];
    }
    matrix[x] = temp_row;
}

void doFunc3(long x, long y){
    x--;
    y--;    
    cout << matrix[x][y] << endl;
}

int main(){
    // n 行, m 列, q 次调整
    cin >> n >> m >> q;
    matrix.resize(n, vector<int>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            matrix[i][j] = i*m + j + 1;
        }
    }
    
    for(int i = 0; i < q; i++){
        long t, x, y;
        cin >> t >> x >> y;
        switch (t) {
            case 1:
                doFunc1(x, y);
                break;
            case 2:                
                doFunc2(x, y);
                break;
            case 3:
                doFunc3(x, y);
                break;
        }
    }
    return 0;
}
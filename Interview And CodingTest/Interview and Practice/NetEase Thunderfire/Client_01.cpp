#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
# 图片拼接问题

## 问题描述
一张图片被裁剪成 \( N \) 行 \( M \) 列，总共 \( N \times M \) 个小图。我们知道每张图片的编号，以及它的上下左右相邻图片的编号。请根据这些信息将图片拼回原来的顺序。

## 输入描述
- 第一行包含两个整数 \( N \) 和 \( M \)，分别表示图片的行数和列数（数字之间用一个空格隔开）。
- 接下来 \( N \times M \) 行，每行包含五个整数，分别表示每张图片的信息：
  - `id x y z w`：其中 `id` 表示图片的编号，`x`、`y`、`z`、`w` 分别表示该图片左、上、右、下四个方向相邻图片的编号。如果相邻图片不存在，则用 `0` 表示。
  
约束条件：
- \( 1 \leq \text{id} \leq N \times M \)
- \( 2 \leq N \leq 100 \)
- \( 2 \leq M \leq 100 \)

> 注意：如果图片的某个相邻方向没有图片，用 `0` 表示。

## 输出描述
输出一个 \( N \times M \) 的正确图片序列编号矩阵，每行包含 \( M \) 个图片编号，每个编号之间用空格隔开。

## 示例

### 输入
```
3 3
1 2 4 8 6
2 0 5 1 7
3 4 0 0 8
4 5 0 3 1
5 0 0 4 2
6 7 1 9 0
7 0 2 6 0
8 1 3 0 9
9 6 8 0 0
```

### 输出
```
5 4 3
2 1 8
7 6 9
```

## 题解思路
1. **输入解析**：读取每张小图的编号和相邻信息，存储为一个数据结构，方便查询每张图片的上下左右邻居。
2. **确定拼接顺序**：找到图片的起始位置（通常是左上角）。起始位置的特征是没有左边和上边的邻居。
3. **遍历拼接**：根据左上角图片的顺序，依次按行遍历拼接整张图片。
4. **输出结果**：将拼接好的图片编号按照矩阵的格式输出。

这样可以还原出正确的图片序列。

*/


struct Image {
    int id;
    int left, top, right, bottom;
};

int main(){
    int N, M;
    cin >> N >> M;

    unordered_map<int, Image> images;
    
    for (int i = 0; i < N * M; i++) {
        int id, left, top, right, bottom;
        cin >> id >> left >> top >> right >> bottom;
        images[id] = {id, left, top, right, bottom};
    }

    vector<vector<int>> result(N, vector<int>(M, 0));

    int start_id = 0;
    for (const auto &image : images) {
        if (image.second.left == 0 && image.second.top == 0) {
            start_id = image.second.id;
            break;
        }    
    }

    int x = 0, y = 0;
    int current_id = start_id;
    while(current_id != 0){
        result[x][y] = current_id;
        int next_id = images[current_id].right;
        if(next_id == 0){
            y = 0;
            x++;
            current_id = images[result[x-1][0]].bottom;
        } else {
            y++;
            current_id = next_id;
        }
    }

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cout << result[i][j];
            if(j < M - 1){
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
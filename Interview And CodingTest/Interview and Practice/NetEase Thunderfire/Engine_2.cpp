#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
### 题目描述：

给定一个3D模型的顶点和组成三角形的顶点索引，询问两点之间的连通关系。

- `N` 表示模型的顶点数量。
- `M` 表示 IB 中存储的三角形数量（每个三角形由 3 个顶点组成）。
- `T` 表示需要查询的两点关系的数量。

接下来 `M` 行，每行 3 个整数，表示组成一个三角形的 3 个顶点的索引。
接下来 `T` 行，每行 2 个整数，表示需要查询的两个顶点的索引。

你需要判断每对顶点之间的关系，并输出对应的连通类型：
- **类型 1**：两个点相邻（在同一个三角形中）。
- **类型 2**：两点可达，但不直接相邻（通过其他顶点间接连接）。
- **类型 3**：两点不可达。

### 输入：
- 第一行输入三个整数 `N`、`M` 和 `T`，分别表示顶点数量、三角形数量和查询数量。
- 接下来 `M` 行，每行 3 个整数，表示组成一个三角形的 3 个顶点索引。
- 接下来 `T` 行，每行 2 个整数，表示需要查询的两个顶点的索引。

### 输出：
输出 `T` 行，每行输出两个查询顶点的连通类型（1, 2 或 3）。

### 输入示例：
```
9 4 5
0 1 2
0 2 3
3 2 4
5 6 7
1 0
1 4
3 6
5 7
6 8
```

### 输出示例：
```
1
2
3
1
3
```

### 说明：
- 点 `1` 和 `0` 直接相邻，因此输出类型 1。
- 点 `1` 和 `4` 不直接相邻但通过其他点可达，因此输出类型 2。
- 点 `3` 和 `6` 不连通，因此输出类型 3。
- 点 `5` 和 `7` 直接相邻，因此输出类型 1。
- 点 `6` 和 `8` 不连通，因此输出类型 3。

### 解题思路：
1. 构建一个无向图，三角形的每个顶点之间都有一条边。
2. 对每次查询，先判断两点是否直接相邻，如果不是，则判断是否连通（可达）。
3. 使用深度优先搜索（DFS）或并查集（Union-Find）来判断连通性。
*/

// 深度优先
void dfs(int node, int flag, vector<int>& canPassWay, vector<vector<int>>& graph){
    // 把一条路径的访问到的位置都给这个ID
    canPassWay[node] = flag;
    // 遍历每一个相邻的顶点
    for(int neighborPoint : graph[node]){
        if(canPassWay[neighborPoint] == -1){
            // 如果没有访问到这个点, 也就是说没有路径的ID, 就继续
            dfs(neighborPoint, flag, canPassWay, graph);
        }       
    }
}

int main() {
    // N个顶点, M个三角面, T个查询
    int N,M,T;
    cin >> N >> M >> T;
    // 图
    vector<vector<int>> graph(N);
    for(int i = 0; i < M; i++){
        int u,v,w;
        cin >> u >> v >> w;
        // 三角形三个点和它的相邻点
        graph[u].push_back(v);
        graph[u].push_back(w);
        graph[v].push_back(u);
        graph[v].push_back(w);
        graph[w].push_back(u);
        graph[w].push_back(v);
    }

    vector<int> canPassWay(N, -1);
    int flag = 0;

    // 遍历每一个顶点
    for (int i = 0 ; i < N ; i++) {
        // 如果这个点没有被访问过
        if(canPassWay[i] == -1){
            dfs(i, flag, canPassWay, graph);
            flag++;
        }
    }

    for(int i = 0; i < T; ++i){
        int a, b;// 顶点
        cin >> a >> b;
        if (canPassWay[a] != canPassWay[b]) {
            cout << 3 << endl;
        }
        else {
            // 如果相邻点有的话
            if(find(graph[a].begin(), graph[a].end(), b) != graph[a].end()){
                cout << 1 << endl;
            }
            else {
                cout << 2 << endl;
            }
        }
    }

    return 0;
}
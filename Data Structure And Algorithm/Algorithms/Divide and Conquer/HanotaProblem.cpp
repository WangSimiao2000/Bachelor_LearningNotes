#include <iostream>
#include <vector>

using namespace std;

/* 汉诺塔问题 */
/*
将原问题 f(n) 划分为两个子问题 f(n-1) 和 f(1), 并按照以下顺序解决这三个子问题
1. 将 n-1 个圆盘从 A 移至 B 
2. 将剩余 1 个圆盘从 A 直接移至 C
3. 将 n-1 个圆盘借助 A 从 B 移至 C
对于这两个子问题 f(n-1) , 可以通过相同的方式进行递归划分, 直至达到最小子问题 f(1), 而 f(1) 的解是已知的, 只需一次移动操作即可
*/

/* 移动一个圆盘 */
void move(vector<int> &src, vector<int> &tar){
    // 从src中取出顶端圆盘
    int top = src.back();
    src.pop_back();
    // 将圆盘放入tar顶部
    tar.push_back(top);
}

/* 求解汉诺塔问题f(i) */
void dfs(int i, vector<int> &src, vector<int> &buf, vector<int> &tar){
    // 如果src中只有一个圆盘, 则直接移动到tar
    if (i == 1){
        move(src, tar);
        return;    
    }
    // 子问题 f(i-1): 将 src 顶部 i-1 个圆盘从 src 借助 tar 移至 buf
    dfs(i-1, src, tar, buf);
    // 子问题 f(1): 将 src 剩余 1 个圆盘直接移至 tar
    move(src, tar);
    // 子问题 f(i-1): 将 buf 顶部 i-1 个圆盘从 buf 借助 src 移至 tar
    dfs(i-1, buf, src, tar);
}

/* 求解汉诺塔问题 */
void solveHanota(vector<int> &A, vector<int> &B, vector<int> &C){
    int n = A.size();
    // 将A顶部将n个圆盘借助B移至C
    dfs(n, A, B, C);
}

int main(){
    vector<int> A = {3, 2, 1};
    vector<int> B, C;

    cout << "A: ";
    for (int i = 0; i < A.size(); i++){
        cout << A[i] << " ";
    }
    cout << endl;

    cout << "B: ";
    for (int i = 0; i < B.size(); i++){
        cout << B[i] << " ";
    }
    cout << endl;

    cout << "C: ";
    for (int i = 0; i < C.size(); i++){
        cout << C[i] << " ";
    }
    cout << endl;
        
    cout << "doing hanota problem..." << endl;
    solveHanota(A, B, C);

    cout << "A: ";
    for (int i = 0; i < A.size(); i++){
        cout << A[i] << " ";
    }
    cout << endl;

    cout << "B: ";
    for (int i = 0; i < B.size(); i++){
        cout << B[i] << " ";
    }
    cout << endl;

    cout << "C: ";
    for (int i = 0; i < C.size(); i++){
        cout << C[i] << " ";
    }
    cout << endl;

    return 0;
}

/* 
语法注释: 
&: 引用, 用于传递参数, 使得函数可以直接修改实参的值, 而不是传递实参的拷贝
*/
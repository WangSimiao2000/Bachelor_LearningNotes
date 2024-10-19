#include <iostream>
#include <vector>

using namespace std;

/* 二叉树节点结构体 */
struct TreeNode {
    int val;          // 节点值
    TreeNode *left;   // 左子节点指针
    TreeNode *right;  // 右子节点指针
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
给定一棵二叉树, 搜索并记录所有值为 n 的节点, 返回节点列表:

前序遍历这棵树，并判断当前节点的值是否为 n 
若是, 则将该节点的值加入结果列表 res 之中
*/
void preOrderFindN(TreeNode *root, int n ,vector<TreeNode*> &res){
    if(root == nullptr)
        return;
    if(root->val == n){
        res.push_back(root);// 将当前节点加入结果列表
    }
    // 递归左右子树
    preOrderFindN(root->left, n, res);
    preOrderFindN(root->right, n, res);
    return;
}

int main(){
    /*
    初始化一棵二叉树
            1
           / \
          2   3
         / \ / \
        4  5 2  4
    */
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(4);

    // 初始化结果列表
    vector<TreeNode*> res;
    // 搜索值为 2 的节点
    preOrderFindN(root, 2, res);
    // 输出结果
    for(auto node : res){
        cout << node->val << " ";
    }
    return 0;
}

// 注意:
// 传入res的时候, 要传入引用, 也就是&, 因为res是一个vector, 如果不传引用, 那么传入的是res的一个拷贝, 对拷贝的操作不会影响原来的res
// 递归的时候, 递归函数的参数要传引用, 因为递归函数的参数是一个拷贝, 对拷贝的操作不会影响原来的参数
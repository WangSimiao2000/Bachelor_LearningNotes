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
给定一棵二叉树, 搜索并记录所有值为 n 的节点, 返回根节点到这些节点的路径:

前序遍历这棵树，并判断当前节点的值是否为 n 
若是, 则将该节点的值加入结果列表 res 之中
此外, 我们需要借助一个列表 path 来记录访问过的节点路径
当访问到值为 n 的节点时, 将 path 中的节点复制并添加近结果列表 res 之中

在每次"尝试"中, 我们通过将当前节点添加进 path 来记录路径;
而在"回退"前, 我们需要将该节点从 path 中弹出, 以恢复本次尝试之前的状态

注意: 弹出操作的实现是通过 path.pop_back() 来实现的
*/

void preOrderFindPathN(TreeNode *root, int n, vector<vector<TreeNode*>> &res, vector<TreeNode*> &path){
    // 递归终止条件
    if(root == nullptr){
        return;
    }
    path.push_back(root);
    if(root->val == n){
        res.push_back(path);
    }
    // 递归左右子树
    preOrderFindPathN(root->left, n, res, path);
    preOrderFindPathN(root->right, n, res, path);
    // 回退: vector 的 pop_back 操作是将最后一个元素弹出
    path.pop_back();
    // 这里的 return 可以省略, 因为函数执行完毕后会自动返回
    // return; 
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
    vector<vector<TreeNode*>> res;
    // 初始化路径列表
    vector<TreeNode*> path;

    // 搜索值为 2 的节点
    preOrderFindPathN(root, 2, res, path);

    // 输出结果
    for(auto path : res){
        for(auto node : path){
            cout << node->val << " ";
        }
        cout << endl;
    }
    
    return 0;
}
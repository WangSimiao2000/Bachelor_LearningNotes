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
给定一棵二叉树, 搜索并记录所有值为 n 的节点, 返回根节点到这些节点的路径, 并要求路径中不包含值为 m 的节点:

前序遍历这棵树，并判断当前节点的值是否为 n 
若是, 则将该节点的值加入结果列表 res 之中
此外, 我们需要借助一个列表 path 来记录访问过的节点路径
当访问到值为 n 的节点时, 将 path 中的节点复制并添加近结果列表 res 之中

在每次"尝试"中, 我们通过将当前节点添加进 path 来记录路径;
而在"回退"前, 我们需要将该节点从 path 中弹出, 以恢复本次尝试之前的状态

为了满足"不包含值为 m 的节点"约束条件, 我们需要添加剪枝操作:
在搜索过程中, 若遇到值为 m 的节点, 则提前返回, 不再继续搜索
*/

void preOrderFindPathNWithoutM(TreeNode *root, int n, int m, vector<vector<TreeNode*>> &res, vector<TreeNode*> &path){
    // 递归终止条件+剪枝操作
    if(root == nullptr || root->val == m){
        return;
    }
    // 将当前节点加入路径
    path.push_back(root);
    // 若当前节点值为 n, 则将路径加入结果列表
    if(root->val == n){
        res.push_back(path);
    }
    // 递归左右子树
    preOrderFindPathNWithoutM(root->left, n, m, res, path);
    preOrderFindPathNWithoutM(root->right, n, m, res, path);
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

    // 搜索值为 2 的节点, 路径中不包含值为 3 的节点
    preOrderFindPathNWithoutM(root, 2, 3, res, path);

    // 输出结果
    for(auto path : res){
        for(auto node : path){
            cout << node->val << " ";
        }
        cout << endl;
    }
    
    return 0;
}
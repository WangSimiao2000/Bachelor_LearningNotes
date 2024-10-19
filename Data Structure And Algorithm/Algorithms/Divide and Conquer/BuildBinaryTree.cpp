#include <unordered_map>
#include <vector>

using namespace std;

/* 二叉树节点结构体 */
struct TreeNode {
    int val;          // 节点值
    TreeNode *left;   // 左子节点指针
    TreeNode *right;  // 右子节点指针
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* 构建二叉树：分治 */

/*
从 preorder 和 inorder 构建二叉树:

> 为什么preorder是数组, inorder是哈希表? 因为preorder是前序遍历，根节点在前，所以可以直接取出根节点的值，而inorder是中序遍历，根节点在中间，所以需要通过哈希表来查找根节点的值。 

- 将当前树的根节点在 preorder 中的索引记为 i
- 将当前树的根节点在 inorder 中的索引记为 m
- 将当前树在 inorder 中的索引区间记为 [l, r], 其中 l 为区间左端点，r 为区间右端点

注意: 右子树根节点索引中的 (m - l) 的含义是"左子树的节点数量"

1. 查找根节点在 inorder 中的索引
2. 利用该索引可将 inorder 划分为 [ 左子树 | 根节点 ｜ 右子树 ]
3. 根据 inorder 的划分结果，易得左子树和右子树的节点数量，从而可将 preorder 划分为 [ 根节点 | 左子树 | 右子树 ]
4. 递归构建左子树和右子树
*/

TreeNode *dfs(vector<int> &preorder, unordered_map<int, int> &inorderMap, int i, int l, int r) {
    // 子树区间为空时终止
    if (r - l < 0)
        return NULL;
    // 初始化根节点
    TreeNode *root = new TreeNode(preorder[i]);
    // 查询 m ，从而划分左右子树
    int m = inorderMap[preorder[i]];
    // 子问题：构建左子树
    root->left = dfs(preorder, inorderMap, i + 1, l, m - 1);
    // 子问题：构建右子树
    root->right = dfs(preorder, inorderMap, i + 1 + m - l, m + 1, r);
    // 返回根节点
    return root;
}

/* 构建二叉树 */
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    // 初始化哈希表，存储 inorder 元素到索引的映射
    unordered_map<int, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++) {
        // 这里的inorderMap的key是inorder的元素，value是元素在inorder中的索引, 目的是为了快速查找根节点在inorder中的索引
        // 给Map赋值的时候，key的值是map的中括号里的值，value是等号右边的值
        inorderMap[inorder[i]] = i;
    }
    TreeNode *root = dfs(preorder, inorderMap, 0, 0, inorder.size() - 1);
    return root;
}

int main(){    
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    TreeNode *root = buildTree(preorder, inorder);
    // 树只需要根节点的指针即可, 其他节点可以通过根节点的指针访问
    return 0;
}
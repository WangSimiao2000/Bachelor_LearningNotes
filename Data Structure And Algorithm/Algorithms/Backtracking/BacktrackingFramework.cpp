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
回溯算法框架 
state 表示问题的当前状态, choices 表示当前状态下可以做出的选择

void backtrack(State *state, vector<Choice *> &choices, vector<State *> &res) {
    // 判断是否为解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res);
        // 不再继续搜索
        return;
    }
    // 遍历所有选择
    for (Choice choice : choices) {
        // 剪枝：判断选择是否合法
        if (isValid(state, choice)) {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            backtrack(state, choices, res);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, choice);
        }
    }
}
*/

/*
基于回溯算法的例题三:
给定一棵二叉树, 搜索并记录所有值为 7 的节点, 返回根节点到这些节点的路径, 并要求路径中不包含值为 3 的节点:
- 状态 state 为节点遍历路径, 用于记录当前节点的路径, 类似上个文件中的 path
- 选择 choices 为当前节点的左子节点和右子节点, 用于表示当前节点的所有可能选择, 类似上个文件中的 root, root->left 和 root->right
- 结果 res 是路径列表, 用于记录所有满足条件的路径
*/

/* 判断当前状态是否为解 */
// 条件: 当前状态不为空, 且最后一个节点的值为 2
bool isSolution(vector<TreeNode *> &state) {
    return !state.empty() && state.back()->val == 2;
}

/* 记录解 */
void recordSolution(vector<TreeNode *> &state, vector<vector<TreeNode *>> &res) {
    res.push_back(state);
}

/* 判断在当前状态下，该选择是否合法 */
// 条件: 选择不为空, 且选择的节点的值不为 3
bool isValid(vector<TreeNode *> &state, TreeNode *choice) {
    return choice != nullptr && choice->val != 3;
}

/* 更新状态 */
void makeChoice(vector<TreeNode *> &state, TreeNode *choice) {
    state.push_back(choice);
}

/* 恢复状态 */
void undoChoice(vector<TreeNode *> &state, TreeNode *choice) {
    state.pop_back();
}

/* 回溯算法：例题三 */
void backtrack(vector<TreeNode *> &state, vector<TreeNode *> &choices, vector<vector<TreeNode *>> &res) {
    // 检查是否为解
    if (isSolution(state)) {
        // 记录解
        recordSolution(state, res);
    }
    // 遍历所有选择
    for (TreeNode *choice : choices) {
        // 剪枝：检查选择是否合法
        if (isValid(state, choice)) {
            // 尝试：做出选择，更新状态
            makeChoice(state, choice);
            // 进行下一轮选择
            vector<TreeNode *> nextChoices{choice->left, choice->right};
            backtrack(state, nextChoices, res);
            // 回退：撤销选择，恢复到之前的状态
            undoChoice(state, choice);
        }
    }
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
    vector<vector<TreeNode *>> res;
    // 初始化状态列表
    vector<TreeNode *> state{root};

    // 搜索值为 2 的节点, 路径中不包含值为 3 的节点
    vector<TreeNode *> choices{root->left, root->right};
    backtrack(state, choices, res);

    // 输出结果
    for (vector<TreeNode *> path : res) {
        for (TreeNode *node : path) {
            cout << node->val << " ";
        }
        cout << endl;
    }
    return 0;
}

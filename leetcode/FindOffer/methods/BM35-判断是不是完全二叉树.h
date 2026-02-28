#include <queue>

#include "../include/struct_define.h"
class isCompleteTreeSolution {
   public:
    // 完全二叉树的性质是：除了最后一层之外，其余层都被填满，且最后一层的节点全部靠左排列。
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;

        std::queue<TreeNode*> q;
        q.push(root);

        bool has_null_encountered = false;
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (!node) {
                has_null_encountered = true;
            } else {
                if (has_null_encountered) {
                    return false;
                }

                q.push(node->left);
                q.push(node->right);
            }
        }

        return true;
    }
};
#include <queue>

#include "../include/struct_define.h"
class TreehasPathSumSolution {
   public:
    // dfs
    bool hasPathSum(TreeNode* root, int sum) {
        // write code here
        if (!root) return false;

        if (sum == root->val && !root->left && !root->right) return true;

        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }

    // bfs
    bool hasPathSumBFS(TreeNode* root, int targetSum) {
        if (!root) return false;

        std::queue<std::pair<TreeNode*, int>> q;
        q.push({root, targetSum - root->val});

        while (!q.empty()) {
            std::pair<TreeNode*, int> current = q.front();
            TreeNode* node = current.first;
            int remain_sum = current.second;
            q.pop();

            if (!node->left && !node->right && 0 == remain_sum) return true;

            if (node->left) q.push({node->left, remain_sum - node->left->val});
            if (node->right) q.push({node->right, remain_sum - node->right->val});
        }

        return false;
    }
};
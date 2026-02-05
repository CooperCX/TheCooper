/*层序遍历：从上到下*/

#include <queue>
#include <vector>

#include "../include/struct_define.h"

// 借助队列，先进先出
class QueueSolution {
   public:
    std::vector<int> lvorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (!root) return results;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            results.push_back(node->val);
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return results;
    }

    std::vector<std::vector<int>> levelOrderTraversal(TreeNode* root) {
        std::vector<std::vector<int>> results;
        if (!root) return results;
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            std::vector<int> current_level;
            int level_size = q.size();
            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();
                current_level.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            results.push_back(current_level);
        }
        return results;
    }
};
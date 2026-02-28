#include <queue>
#include <vector>

#include "../include/struct_define.h"

class printTreeByZhiTypeSolution {
   public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> results;
        if (!root) return results;

        std::queue<TreeNode*> q;
        q.push(root);

        bool is_left_to_right = true;

        while (!q.empty()) {
            int level_size = q.size();
            std::vector<int> current_level(level_size);
            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();
                int index = is_left_to_right ? i : level_size - 1 - i;
                current_level[index] = node->val;

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            is_left_to_right = !is_left_to_right;
            results.push_back(std::move(current_level));
        }
        return results;
    }
};
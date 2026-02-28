#include <queue>
#include <vector>

#include "../include/struct_define.h"

class RightViewOfTreeSolution {
   public:
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> results;
        if (!root) return results;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int current_level_size = q.size();

            for (int i = 0; i < current_level_size; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (i == current_level_size - 1) results.push_back(node->val);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }

        return results;
    }
};
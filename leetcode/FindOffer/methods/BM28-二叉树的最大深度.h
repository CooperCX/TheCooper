#include <algorithm>
#include <queue>

#include "../include/struct_define.h"

class TreeDepthSolution {
   public:
    // DFS 递归
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return 0;
        }
        return std::max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
    }

    // BFS 实现：防爆栈
    int maxDepth(TreeNode* root) {
        if (!root) return 0;

        std::queue<TreeNode*> q;
        q.push(root);

        int depth = 0;
        while (!q.empty()) {
            int level_size = q.size();
            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            depth++;
        }

        return depth;
    }
};
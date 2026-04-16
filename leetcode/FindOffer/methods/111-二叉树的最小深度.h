#include <algorithm>  // 引入 std::abs 和 std::max
#include <queue>
#include <vector>

#include "../include/struct_define.h"

inline int minDepthDFS(TreeNode* root) {
    if (!root) return 0;
    if (!root->left) return minDepthDFS(root->right) + 1;
    if (!root->right) return minDepthDFS(root->left) + 1;

    return std::min(minDepthDFS(root->left), minDepthDFS(root->right)) + 1;
}

inline int minDepthBFS(TreeNode* root) {
    if (!root) return 0;

    std::queue<TreeNode*> q;
    q.push(root);

    int min_depth = 1;
    while (!q.empty()) {
        int current_size = q.size();
        for (int i = 0; i < current_size; ++i) {
            TreeNode* node = q.front();
            q.pop();
            if (!node->left && !node->right) return min_depth;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        min_depth++;
    }

    return min_depth;
}
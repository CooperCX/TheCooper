#include <queue>
#include <utility>

#include "../include/struct_define.h"
class MirrorTreeSolution {
   public:
    TreeNode* Mirror(TreeNode* pRoot) {
        if (!pRoot) return nullptr;

        std::swap(pRoot->left, pRoot->right);

        Mirror(pRoot->left);
        Mirror(pRoot->right);

        return pRoot;
    }

    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            std::swap(node->left, node->right);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return root;
    }
};
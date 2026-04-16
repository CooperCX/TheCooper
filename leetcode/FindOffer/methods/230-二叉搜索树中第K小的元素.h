#include "../include/struct_define.h"
#include <stack>

class KthNodeSolution {
    TreeNode* KthNode(TreeNode* root, int k) {
        if (root == nullptr) {
            return nullptr;
        }
        std::stack<TreeNode*> s;
        while (!s.empty() || root != nullptr) {
            while (root) {
                s.push(root);
                root = root->left;
            }
            k--;
            TreeNode* node = s.top();
            if (k == 0) {
                return node;
            }
            s.pop();

            if (node->right) {
                root = node->right;
            }
        }
    }
};
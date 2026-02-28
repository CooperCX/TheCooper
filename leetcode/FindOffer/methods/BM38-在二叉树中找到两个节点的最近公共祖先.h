#include "../include/struct_define.h"

class lowestCommonAncestorSolution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;

        if (root->val == p->val || root->val == q->val) return root;

        TreeNode* leftRes = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightRes = lowestCommonAncestor(root->right, p, q);

        if (!leftRes) return rightRes;
        if (!rightRes) return leftRes;

        return root;
    }
};
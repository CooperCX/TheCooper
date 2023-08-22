#include "../include/struct_define.h"

class lowestCommonAncestorSolution {
public:

    int lowestCommonAncestor(TreeNode* root, int p, int q) {
        if (p > q) {
            int temp = p;
            q = temp;
        }

        if (p <= root->val && q >= root->val) {
            return root->val;
        } else if (p < root->val && q < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else {
            return lowestCommonAncestor(root->right, p, q);
        }
    }
};
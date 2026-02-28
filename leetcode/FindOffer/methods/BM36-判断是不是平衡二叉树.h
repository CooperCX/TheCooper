#include <algorithm>

#include "../include/struct_define.h"

class IsBalancedSolution {
   public:
    bool isBalanced(TreeNode* root) { return TreeDepth(root) != -1; }

   private:
    int TreeDepth(TreeNode* root) {
        if (!root) return 0;

        int leftDepth = TreeDepth(root->left);
        if (-1 == leftDepth) return -1;
        int rightDepth = TreeDepth(root->right);
        if (-1 == rightDepth) return -1;

        if (std::abs(leftDepth - rightDepth) > 1) return -1;

        return std::max(leftDepth, rightDepth) + 1;
    }
};
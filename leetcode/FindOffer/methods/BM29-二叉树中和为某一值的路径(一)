#include "../include/struct_define.h"

class TreehasPathSumSolution {
public:

    bool hasPathSum(TreeNode* root, int sum) {
        // write code here
        if (root == nullptr) {
            return false;
        }
        if (root->val == sum && root->left == nullptr && root->right == nullptr) {
            return true;
        }
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }


};
#include "../include/struct_define.h"

class isSymmetricalSolution {
public:
    bool isSymmetrical(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return true;
        }
        return isMirror(pRoot->left, pRoot->right);
    }
private:
    bool isMirror(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right == nullptr) {
            return true;
        }
        if (left == nullptr || right == nullptr) {
            return false;
        }
        if (left->val == right->val) {
            return isMirror(left->left, right->right) && isMirror(left->right, right->left);
        } else {
            return false;
        }
    }
};
#include <algorithm>
#include "../include/struct_define.h"

class IsBalancedSolution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return true;
        }
        return TreeDepth(pRoot) != -1;
    }
private:
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return 0;
        }
        int left = TreeDepth(pRoot->left);
        if (left == -1) {
            return -1;
        }
        int right = TreeDepth(pRoot->right);
        if (right == -1) {
            return -1;
        }
        if (std::abs(right - left) <= 1) {
            return std::max(right, left) + 1;
        } else {
            return -1;
        }
    }
};
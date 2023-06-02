#include <algorithm>
#include "struct_define.h"

class Solution {
public:
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return 0;
        }
        int left = 0, right = 0;
        if (pRoot->left) {
            left = TreeDepth(pRoot->left);
        }
        if (pRoot->right) {
            right = TreeDepth(pRoot->right);
        }
        return std::max(left, right) + 1;
    }
};
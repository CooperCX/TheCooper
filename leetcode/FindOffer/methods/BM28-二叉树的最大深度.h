#include <algorithm>
#include "../include/struct_define.h"

class TreeDepthSolution {
public:
    int TreeDepth(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return 0;
        }
        return std::max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
    }
};
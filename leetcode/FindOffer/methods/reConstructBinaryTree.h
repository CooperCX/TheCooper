#include <vector>
#include <algorithm>
#include "../include/struct_define.h"

/*
递归思想
在中序中找到root的位置，左边为左子树，右边为右子树，根据左子树和右子树的节点数，找到前序中的左子树和右子树
分别重建左子树和右子树
*/
class reConstructBinaryTreeSolution {
public:
    TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin) {
        if (pre.size() == 0 || vin.size() == 0) {
            return nullptr;
        }

        TreeNode* root = new TreeNode(pre[0]);
        auto iter = std::find(vin.begin(), vin.end(), pre[0]);
        int root_index = std::distance(vin.begin(), iter);

        std::vector<int> left_pre(pre.begin() + 1, pre.begin() + root_index + 1);
        std::vector<int> right_pre(pre.begin() + root_index + 1, pre.end());

        std::vector<int> left_vin(vin.begin(), vin.begin() + root_index);
        std::vector<int> right_vin(vin.begin() + root_index + 1, vin.end());

        root->left = reConstructBinaryTree(left_pre, left_vin);
        root->right = reConstructBinaryTree(right_pre, right_vin);

        return root;
    }
};

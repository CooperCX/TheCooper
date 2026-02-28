#include <algorithm>
#include <unordered_map>
#include <vector>

#include "../include/struct_define.h"

/*
递归思想
在中序中找到root的位置，左边为左子树，右边为右子树，根据左子树和右子树的节点数，找到前序中的左子树和右子树
分别重建左子树和右子树
*/
class reConstructBinaryTreeSolution {
   public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) return nullptr;

        std::unordered_map<int, int> inorder_map;
        for (int i = 0; i < inorder.size(); i++) {
            inorder_map[inorder[i]] = i;
        }

        return reConstructBinaryTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inorder_map);
    }

    TreeNode* reConstructBinaryTree(const std::vector<int>& preorder, int pre_left, int pre_right,
                                    const std::vector<int>& inorder, int vin_left, int vin_right,
                                    const std::unordered_map<int, int>& inorder_map) {
        if (pre_left > pre_right) return nullptr;

        int root_val = preorder[pre_left];
        TreeNode* root = new TreeNode(root_val);

        int root_index_in_inorder = inorder_map.at(root_val);
        int left_tree_size = root_index_in_inorder - vin_left;

        root->left = reConstructBinaryTree(preorder, pre_left + 1, pre_left + left_tree_size, inorder, vin_left,
                                           root_index_in_inorder - 1, inorder_map);
        root->right = reConstructBinaryTree(preorder, pre_left + left_tree_size + 1, pre_right, inorder,
                                            root_index_in_inorder + 1, vin_right, inorder_map);

        return root;
    }
};

#include <climits>
#include <stack>
#include <vector>

#include "../include/struct_define.h"

// 二叉搜索树的中序遍历是递增的
class isValidBSTSolution {
   public:
    // 中序递归
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = nullptr;
        return InorderCheck(root, pre);
    }

    bool InorderCheck(TreeNode* root, TreeNode*& pre) {
        if (!root) return true;

        if (!InorderCheck(root->left, pre)) return false;

        if (pre && root->val <= pre->val) return false;
        pre = root;

        return InorderCheck(root->right, pre);
    }

    // 借助栈
    bool isValidBST2(TreeNode* root) {
        if (!root) return false;

        std::stack<TreeNode*> s;
        TreeNode* pre = nullptr;
        while (!s.empty() || root) {
            while (root) {
                s.push(root);
                root = root->left;
            }

            root = s.top();
            s.pop();

            if (pre && root->val <= pre->val) return false;
            pre = root;

            root = root->right;
        }
        return true;
    }
};
#include "../include/struct_define.h"
#include <climits>
#include <vector>
#include <stack>

// 二叉搜索树的中序遍历是递增的
class isValidBSTSolution {
public:
    // 中序递归
    int pre = INT_MIN;
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        if (!isValidBST(root->left)) {
            return false;
        }
        if (root->val < pre) {
            return false;
        }
        pre = root->val;
        if (!isValidBST(root->right)) {
            return false;
        }
        return true;
    }

    // 借助栈
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        std::stack<TreeNode*> s;
        std::vector<int> temp;
        while (!s.empty() || root != nullptr) {
            while (root != nullptr) {
                s.push(root);
                root = root->left;
            }
            TreeNode* node = s.top();
            s.pop();
            temp.push_back(node->val);
            root = node->right;
        }
        for (int i = 1; i < temp.size(); i++) {
            if (temp[i] < temp[i - 1]) {
                return false;
            }
        }
        return true;
    }
};
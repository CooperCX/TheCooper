/*后序遍历：左-右-根*/

#include <vector>
#include "stack.h"
#include "struct_define.h"

//递归解法
class RecursionSolution {
public:
    void postorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) {
            return;
        }
        if (node->left) {
            postorder(node->right, res);
        }
        if (node->right) {
            postorder(node->left, res);
        }
        res.emplace_back(node->val);
    }

    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;

        postorder(root, results);
        return results;
    }
};


//借助栈
class StackSolution {
public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) {
            return results;
        }
        stack<TreeNode*> s;
        TreeNode* pre = nullptr;
        while (!s.empty() || root != nullptr) {
            while (root != nullptr) {
                s.push(root);
                root = root->left;
            }
            TreeNode* node = s.top();
            s.pop();
            if (node->right == nullptr || node->right == pre) {
                results.emplace_back(node->val);
                pre = node;
            } else {
                s.push(node);
                root = node->right;
            }
        }

        return results;
    }
};
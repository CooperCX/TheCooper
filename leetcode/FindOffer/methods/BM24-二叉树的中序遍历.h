/*中序遍历：左-根-右*/

#include <vector>

#include "../include/stack.h"
#include "../include/struct_define.h"

// 递归解法
class RecursionSolution {
   public:
    void inorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) return;
        inorder(node->left, res);
        res.emplace_back(node->val);
        inorder(node->right, res);
    }

    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;
        inorder(root, results);
        return results;
    }
};

// 借助栈
class StackSolution {
   public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (!s.empty() || cur) {
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }

            cur = s.top();
            s.pop();
            results.push_back(cur->val);
            cur = cur->right;
        }

        return results;
    }
};
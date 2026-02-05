/*后序遍历：左-右-根*/

#include <vector>

#include "../include/stack.h"
#include "../include/struct_define.h"

// 递归解法
class RecursionSolution {
   public:
    void postorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) return;
        postorder(node->left, res);
        postorder(node->right, res);
        res.emplace_back(node->val);
    }

    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        postorder(root, results);
        return results;
    }
};

// 借助栈
class StackSolution {
   public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (!root) return results;
        stack<TreeNode*> s;
        TreeNode* prev = nullptr;
        TreeNode* curr = root;
        while (!s.empty() || curr) {
            while (curr) {
                s.push(curr);
                curr = curr->left;
            }

            curr = s.top();
            if (!curr->right || curr->right == prev) {
                s.pop();
                results.push_back(curr->val);
                prev = curr;
                curr = nullptr;
            } else {
                curr = curr->right;
            }
        }
        return results;
    }
};
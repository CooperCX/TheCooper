#include <vector>
#include "stack.h"
#include "struct_define.h"


// 递归解法
class RecursionSolution {
public:
    void inorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) {
            return;
        }
        if (node->left) {
            inorder(node->left, res);
        }
        res.emplace_back(node->val);
        if (node->right) {
            inorder(node->right, res);
        }
    }

    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;

        inorder(root, results);
        return results;
    }
};


//借助栈
class StackSolution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) {
            return results;
        }
        stack<TreeNode*> s;
        while (root != nullptr || !s.empty())
        {
            while(root != nullptr) {
                s.push(root);
                root = root->left;
            }
            TreeNode* node = s.top();
            s.pop();
            results.emplace_back(node->val);
            if (node->right) {
                root = node->right;
            }
        }
        
        return results;
    }
};
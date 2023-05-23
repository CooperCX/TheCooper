/*前序遍历：根-左-右*/

#include <vector>
#include "stack.h"
#include "struct_define.h"


// 递归
class Solution {
public:
    void preorder(TreeNode* root, std::vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        res.emplace_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }

    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> results;
        preorder(root, results);
        return results;
    }
};

//栈
class Solution {
public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) {
            return results;
        }
        stack<TreeNode*> s;
        s.push(root);
        while(!s.empty()) {
            TreeNode* node = s.top();
            results.emplace_back(node->val);
            s.pop();
            if(node->right) {
                s.push(node->right);
            }
            if(node->left) {
                s.push(node->left);
            }
        }
        return results;
    }
};
#include <vector>
#include "stack.h"

struct TreeNode
{
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val, TreeNode* left, TreeNode* right) :
        val(val), left(left), right(right) {}
};


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
        s.push_back(root);
        while(!s.empty()) {
            TreeNode* node = s.top();
            results.emplace_back(node->val);
            s.pop();
            if(node->right) {
                s.push_back(node->right);
            }
            if(node->left) {
                s.push_back(node->left);
            }
        }
        return results;
    }
};
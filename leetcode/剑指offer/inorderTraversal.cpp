#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val, TreeNode* left, TreeNode* right) :
        val(val), left(left), right(right) {}
};

class Solution {
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

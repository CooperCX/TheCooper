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
    void postorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) {
            return;
        }
        if (node->left) {
            postorder(node->right, res);
        }
        res.emplace_back(node->val);
        if (node->right) {
            postorder(node->left, res);
        }
    }

    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;

        postorder(root, results);
        return results;
    }
};

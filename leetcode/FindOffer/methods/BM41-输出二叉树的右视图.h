#include <vector>
#include <queue>
#include "../include/struct_define.h"
#include "BM40-重建二叉树.h"

class RightViewOfTreeSolution {
public:

    std::vector<int> solve(std::vector<int>& preOrder, std::vector<int>& inOrder) {
        TreeNode* root = reConstructBinaryTreeSolution::reConstructBinaryTree(preOrder, inOrder);
        std::vector<int> results;
        if (root == nullptr) {
            return results;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int len = q.size();
            results.push_back(q.back()->val);
            while (len > 0) {
                TreeNode* node = q.front();
                q.pop();
                len--;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }
        return results;
    }
};
#include "../include/struct_define.h"
#include <queue>
class isCompleteTreeSolution {
public:

    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        bool flag = false;
        while (!q.empty()) {
            int len = q.size();
            while (len > 0) {
                TreeNode* node = q.front();
                q.pop();
                len--;
                if (node == nullptr) {
                    flag = true;
                } else {
                    if (flag) {
                        return false;
                    }
                    q.push(node->left);
                    q.push(node->right);
                }
            }
        }
        return true;
    }
};
/*层序遍历：从上到下*/

#include <vector>
#include <queue>
#include "struct_define.h"

// 借助队列，先进先出
class QueueSolution {
public:
    std::vector<int> lvorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) {
            return results;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            results.push_back(node->val);
            q.pop();
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
        return results;
    }
};
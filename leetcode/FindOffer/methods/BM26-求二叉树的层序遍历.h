/*层序遍历：从上到下*/

#include <vector>
#include <queue>
#include "../include/struct_define.h"

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

    std::vector<std::vector<int>> levelOrderTraversal(TreeNode* root) {
        std::vector<std::vector<int>> results;
        if (nullptr == root) {
            return results;
        }
        std::queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            std::vector<int> temp;
            int len = q.size();
            while (len > 0) {
                TreeNode* node = q.front();
                temp.push_back(node->val);
                q.pop();
                len--;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            results.push_back(temp);
        }
        return results;
    }
};
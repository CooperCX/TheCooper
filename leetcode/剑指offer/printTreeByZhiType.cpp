#include <vector>
#include <queue>
#include "struct_define.h"

class Solution {
public:
    std::vector<std::vector<int> > Print(TreeNode* pRoot) {
        std::vector<std::vector<int>> results;
        if (pRoot == nullptr) {
            return results;
        }
        std::queue<TreeNode*> q;
        q.push(pRoot);
        bool isLeft = true;
        while (!q.empty()) {
            std::vector<int> temp;
            int len = q.size();
            while (len > 0) {
                TreeNode* node = q.front();
                q.pop();
                temp.push_back(node->val);
                len--;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            if (isLeft) {
                results.push_back(temp);
            } else {
                results.push_back(std::vector<int>(temp.rbegin(), temp.rend()));
            }
            isLeft = !isLeft;
        }
        return results;
    }
};
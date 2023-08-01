#include <vector>
#include "../include/struct_define.h"

class FindPathSolution {
public:
    std::vector<std::vector<int>> FindPath(TreeNode* root, int expectNumber) {
        std::vector<std::vector<int>> results;
        std::vector<int> temp;
        FindPathCore(root, expectNumber, results, temp);
        return results;
    }
private:
    void FindPathCore(TreeNode* root, int expectNumber,
                      std::vector<std::vector<int>>& results,
                      std::vector<int>& temp) {
        if (root == nullptr) {
            return;
        }
        temp.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr && root->val == expectNumber) {
            results.push_back(temp);
        }
        expectNumber = expectNumber - root->val;
        FindPathCore(root->left, expectNumber, results, temp);
        FindPathCore(root->right, expectNumber, results, temp);
        temp.pop_back();
    }
};
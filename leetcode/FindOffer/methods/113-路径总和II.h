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
    void FindPathCore(TreeNode* root, int expectNumber, std::vector<std::vector<int>>& results,
                      std::vector<int>& temp) {
        if (root == nullptr) {
            return;
        }

        // 1. 做出选择：把当前节点暂存进篮子
        temp.push_back(root->val);

        // 2. 检查是否到达终点叶子节点，且数值达标
        if (root->left == nullptr && root->right == nullptr && root->val == expectNumber) {
            results.push_back(temp);

            // 【极限优化】既然已经是叶子节点，没必要再向下递归找空指针。
            // 但一定要记得先把刚才吃进去的 root->val 吐出来，再 return 退回给父节点！
            temp.pop_back();
            return;
        } else {
            // 3. 向下传递递归：不用传 expectNumber 副本了，直接用数学表达式即可
            // 这也是利用「传值」的隔离性特性
            FindPathCore(root->left, expectNumber - root->val, results, temp);
            FindPathCore(root->right, expectNumber - root->val, results, temp);

            // 4. 撤销选择：离开当前节点回到上一层前，必须从篮子里把自己的痕迹抹除
            temp.pop_back();
        }
    }
};
/*中序遍历：左-根-右*/

#include <vector>

#include "../include/stack.h"
#include "../include/struct_define.h"

// 递归解法
class RecursionSolution {
   public:
    void inorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) return;
        inorder(node->left, res);
        res.emplace_back(node->val);
        inorder(node->right, res);
    }

    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;
        inorder(root, results);
        return results;
    }
};

// 借助栈
class StackSolution {
   public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> results;
        stack<TreeNode*> s;  // 记得加上 std::

        TreeNode* cur = root;  // 探路员指针

        // 当栈里还有节点在等待被处理，或者探路员还没掉下悬崖时，继续循环
        while (!s.empty() || cur != nullptr) {
            // 阶段 1：疯狂往左扎，把一路上的节点全都当作未来要处理的“中”雪藏在栈里
            while (cur != nullptr) {
                s.push(cur);
                cur = cur->left;
            }
            // 阶段 2：左边终于没路了，开始出栈
            // 此时出栈的一定是刚刚被一路向下压栈的链条的最底层（由于后进先出）
            cur = s.top();
            s.pop();

            // 终于可以处理这个节点了（因为它的左边已经绝对没路了）
            results.push_back(cur->val);
            // 阶段 3：左边处理完了，中间也处理完了，去探索这个节点的右边区域！
            // 探路员指向身旁的右子树，下一轮又会进入疯狂往左扎的循环。
            cur = cur->right;
        }
        return results;
    }
};
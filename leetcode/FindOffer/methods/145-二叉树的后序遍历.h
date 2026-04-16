/*后序遍历：左-右-根*/

#include <vector>

#include "../include/stack.h"
#include "../include/struct_define.h"

// 递归解法
class RecursionSolution {
   public:
    void postorder(TreeNode* node, std::vector<int>& res) {
        if (node == nullptr) return;
        postorder(node->left, res);
        postorder(node->right, res);
        res.emplace_back(node->val);
    }

    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        postorder(root, results);
        return results;
    }
};

// 借助栈
class StackSolution {
   public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) return results;

        stack<TreeNode*> s;
        TreeNode* prev = nullptr;  // 记录上一个被完全处理输出的节点
        TreeNode* curr = root;     // 探路员

        while (!s.empty() || curr != nullptr) {
            // 阶段 1：疯狂往左扎，全部压栈保护
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            // 阶段 2：探底了，拿栈顶出来看一眼（不着急弹栈，因为还得回来处理）
            curr = s.top();

            // 如果它没右孩子，或者它的右边所有事都已经干完了（prev 是刚从右边上来的）
            if (curr->right == nullptr || curr->right == prev) {
                s.pop();                       // 把它弹出
                results.push_back(curr->val);  // 处理（中）
                prev = curr;                   // 更新处理名单
                curr = nullptr;                // 探路员置空，下一轮被迫继续弹栈
            } else {
                // 如果它右边还有活没干，探路员去它右边，下一轮又是一翻往左狂扎
                curr = curr->right;
            }
        }
        return results;
    }
};

// ==========================================
// 【黑魔法解法】：前序变异翻转法
// ==========================================
class MagicStackSolution {
   public:
    std::vector<int> postorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) return results;
        stack<TreeNode*> s;
        s.push(root);
        // 像写普通的前序遍历一模一样，只是压栈顺序反过来
        while (!s.empty()) {
            TreeNode* curr = s.top();
            s.pop();
            // 当前顺序：中
            results.push_back(curr->val);
            // 前序是先右后左，这回我们【先左后右】！
            if (curr->left != nullptr) s.push(curr->left);
            if (curr->right != nullptr) s.push(curr->right);
        }
        // 此时 results 存的是 [中, 右, 左]
        // 一个 reverse，直接变成 [左, 右, 中]，这就是正宗后序！
        std::reverse(results.begin(), results.end());
        return results;
    }
};
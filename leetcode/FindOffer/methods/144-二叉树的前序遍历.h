/*前序遍历：根-左-右*/

#include <vector>

#include "../include/stack.h"
#include "../include/struct_define.h"

class preorderSolution {
   public:
    void preorder(TreeNode* root, std::vector<int>& res) {
        if (root == nullptr) return;

        // 前序遍历核心三行：
        res.emplace_back(root->val);  // 1. 先打印中 (根)
        preorder(root->left, res);    // 2. 再遍历左
        preorder(root->right, res);   // 3. 最后遍历右
    }
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> results;
        preorder(root, results);
        return results;
    }
};
// 2. 迭代解法 (面试必考，利用栈模拟系统调用栈)
class preorderSolutionByStack {
   public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> results;
        // 【防御性编程】空树直接返回空集
        if (root == nullptr) return results;
        stack<TreeNode*> s;
        // 初始时先把根节点扔进去
        s.push(root);
        while (!s.empty()) {
            // 每次弹出来的，就是我们要处理的“中”节点
            TreeNode* node = s.top();
            s.pop();

            // 访问“中”
            results.push_back(node->val);
            // 【极度核心】因为栈是后进先出（LIFO）
            // 我们要在下一轮优先处理左子树，必须把左子树最后压栈（放在顶端）
            // 只有**先右后左**地压入，弹出来的时候才是**先左后右**！
            if (node->right != nullptr) s.push(node->right);
            if (node->left != nullptr) s.push(node->left);
        }

        return results;
    }
};
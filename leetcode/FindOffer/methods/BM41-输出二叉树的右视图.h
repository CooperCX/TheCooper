/*
    输出二叉树的右视图
    核心思想：带分层的层序遍历 (BFS)
    右视图的本质：每一层级中最右侧（最后出队）的那个节点！
*/

#include <queue>
#include <vector>

#include "../include/struct_define.h"

class RightViewOfTreeSolution {
   public:
    // 解法：BFS 层序遍历 (队列)
    // 时间复杂度：O(N) (每个节点进出队列一次)
    // 空间复杂度：O(N) (最底层节点数量，队列开销)
    std::vector<int> rightSideView(TreeNode* root) {
        std::vector<int> results;
        // 【防御】树为空，你啥也看不见
        if (root == nullptr) return results;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            // 这个变量极其关键！它锁死了当前“这一层”的人数。
            // 稍后队列里虽然会不停地加入下一层的新人，但在内部的 for 循环里，
            // 我们绝对只会处理属于这一层的这 current_level_size 个人。
            int current_level_size = q.size();

            for (int i = 0; i < current_level_size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 【核心逻辑】：
                // 因为入队顺序是“先左后右”，所以出队顺序是“从左到右扫描”
                // 当 i 等于当前层人数减 1 时，说明它是这一层的【最后一个节点】
                // 也就是站在最右侧、唯一没有被别人挡住的面孔！
                if (i == current_level_size - 1) {
                    results.push_back(node->val);
                }

                // 把当前节点的下一代推入队列结尾排队，留给下一次大循环去审查
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }

        return results;
    }
};

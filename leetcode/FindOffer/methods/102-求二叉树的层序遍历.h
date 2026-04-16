/* 二叉树层序遍历：BFS 广度优先搜索 模板 */
#include <queue>
#include <vector>

#include "../include/struct_define.h"
class QueueSolution {
   public:
    // 问法 1：不需要区分层级，把整棵树铺平成一维数组
    // 时间复杂度 O(N)，空间复杂度 O(N) (队列最大占用约为树的底端宽度 N/2)
    std::vector<int> lvorderTraversal(TreeNode* root) {
        std::vector<int> results;
        if (root == nullptr) return results;  // 【防御】

        std::queue<TreeNode*> q;  // 必须使用先进先出的队列
        q.push(root);             // 根节点率先入队排第一

        while (!q.empty()) {
            TreeNode* node = q.front();  // 队首出列
            q.pop();

            results.push_back(node->val);

            // 它的左膀右臂去队尾继续排队 (谁先来谁先入队)
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        return results;
    }
    // 问法 2：需要明确按层级划分，返回二维数组 (最高频考法)
    std::vector<std::vector<int>> levelOrderTraversal(TreeNode* root) {
        std::vector<std::vector<int>> results;
        if (root == nullptr) return results;

        std::queue<TreeNode*> q;
        q.push(root);

        // 外层循环：控制“层”的推进，只要队列不空，说明还有下一层
        while (!q.empty()) {
            std::vector<int> current_level;  // 本层的专属收纳盒

            // 【极其核心】记录当前队列中有多少个节点，这正是本层的节点总数！
            // 必须提前存入变量，不可写进 for 循环的边界判定中，因为 q.size() 随时在变！
            int level_size = q.size();

            // 内层循环：专门清空当前这一层的所有节点
            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 本层节点入盒
                current_level.push_back(node->val);

                // 【孕育下一代】将它们的孩子塞入队列尾部，留给下一轮外层 while 循环去慢慢享用
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }

            // 本层大丰收，整体加入最终结果
            results.push_back(current_level);
        }
        return results;
    }
};
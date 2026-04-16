#include <queue>
#include <vector>

#include "../include/struct_define.h"

class printTreeByZhiTypeSolution {
   public:
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        std::vector<std::vector<int>> results;
        if (root == nullptr) return results;  // 【防御】
        std::queue<TreeNode*> q;
        q.push(root);
        // 维护一个开关，控制这一层是从左填还是从右填
        bool is_left_to_right = true;
        while (!q.empty()) {
            int level_size = q.size();  // 快照定死本层人数

            // 【极其核心】必须提前分配好容量！因为后面我们不是 push_back，而是靠 index 精准插空
            std::vector<int> current_level(level_size);

            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // 【奇偶分流定位】
                // 如果是奇数层 (从左向右)：正常的 0, 1, 2...
                // 如果是偶数层 (从右向左)：倒数的 尾巴, 尾巴-1, 尾巴-2...
                int index = is_left_to_right ? i : level_size - 1 - i;

                // 空降对号入座，完美避开事后的 std::reverse
                current_level[index] = node->val;
                // 重点：【入队的顺序永远不能变！】
                // 无论是奇数层还是偶数层，孩子节点入队的顺序永远是【先左后右】！
                // 因为子代入队的顺序决定了下一层的原本样子，要是乱放，整棵树都错位了。
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
            // 这一层干完了，把开关状态取反，迎接下一层
            is_left_to_right = !is_left_to_right;

            // 【高阶工程素养】使用 std::move 榨干性能，避免拷贝构造
            results.push_back(std::move(current_level));
        }

        return results;
    }
};
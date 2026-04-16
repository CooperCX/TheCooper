/*
    检验是否为完全二叉树
    核心思想：层序遍历，一旦遇到空节点，其后绝对不能再出现任何实节点！
*/

#include <queue>

#include "../include/struct_define.h"

class isCompleteTreeSolution {
   public:
    // 解法：基于 bool 旗帜位的层序遍历
    // 时间复杂度：O(N)，每个节点入队出队一次
    // 空间复杂度：O(N)，最宽处的下一层可能全是 null，会短暂充满队列
    bool isCompleteTree(TreeNode* root) {
        // 空树本身就是完全二叉树
        if (root == nullptr) return true;

        std::queue<TreeNode*> q;
        q.push(root);

        // 核心雷达旗帜：是否已经在层序遍历中摸到了 nullptr？
        bool has_null_encountered = false;

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            if (node == nullptr) {
                // 一旦查出有空洞，警钟长鸣！
                // 这意味着，按层序遍历的顺序，这棵树的实体节点【理应】已经完全发完了
                has_null_encountered = true;
            } else {
                // 如果当前摸出了一个实打实的节点
                if (has_null_encountered == true) {
                    // 但警钟早在前面就已经敲响了！
                    // 说明在当前节点的前面，居然存在断裂的坑位
                    // 这违背了“紧致靠左排列”的原则，直接宣判死刑
                    return false;
                }

                // 【神之一手】不加判断，不管是不是 null，统统暴力推入队列！
                // 这与普通的层序遍历（要判空才入队）截然不同
                q.push(node->left);
                q.push(node->right);
            }
        }

        // 巡视全树，除了树尾巴那一堆连绵不绝的 null 之外，中间没有任何断层
        return true;
    }
};

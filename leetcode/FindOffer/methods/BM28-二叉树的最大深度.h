#include <algorithm>
#include <queue>

#include "../include/struct_define.h"
class TreeDepthSolution {
   public:
    // 解法 1：DFS 深搜 (递归)
    // 优点：代码极度优美简洁
    // 缺点：如果树极度不平衡且深度巨大，存在导致系统调用栈溢出的风险
    // 时间复杂度 O(N)，空间复杂度 O(H) (H为树的高度，用于递归调用栈)
    int TreeDepth(TreeNode* pRoot) {
        // 递归触底条件：空节点对深度的贡献为 0
        if (pRoot == nullptr) {
            return 0;
        }

        // 分治与汇总：拿左边和右边的最大深度，加上自己这一楼 (1)，汇报给上级
        return std::max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
    }
    // ============================================
    // 解法 2：BFS 广搜 (层序遍历迭代版)
    // 优点：工业界绝对安全，防爆栈（因为动态分配在堆内存而不是栈内存）
    // 缺点：如果树非常胖（完全二叉树），队列会消耗较多短期内存
    // 时间 O(N)，空间 O(N) (最底层节点数量大约为 N/2)
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;  // 【防御】
        std::queue<TreeNode*> q;
        q.push(root);
        int depth = 0;  // 记录我们到底过了几关

        // 只要还有下一层未通关
        while (!q.empty()) {
            // 每圈 while 就代表闯进了一层！

            // 快照锁定这一层的敌人数量
            int level_size = q.size();

            // 歼灭本层所有敌人
            for (int i = 0; i < level_size; i++) {
                TreeNode* node = q.front();
                q.pop();
                // 把下一层的敌人加到备战区
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }

            // 这一层的苦工完成了，深度 +1
            depth++;
        }
        return depth;
    }
};
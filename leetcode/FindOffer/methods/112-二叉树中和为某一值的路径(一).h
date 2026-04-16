#include <queue>
#include <utility>  // 必须引入以使用 std::pair

#include "../include/struct_define.h"

class TreehasPathSumSolution {
   public:
    // ==========================================
    // 解法 1：DFS 递归深搜 (自顶向下减法思想)
    // 时间 O(N)，空间 O(H) (H 为递归栈深度)
    // ==========================================
    bool hasPathSum(TreeNode* root, int sum) {
        // 【防御】空节点，绝对凑不出任何路径
        if (root == nullptr) return false;

        // 【成功判定】必须同时满足两个条件：
        // 1. 它是叶子节点 (没有左右孩子)
        // 2. 扣除之前的过路费后，剩下的穷举额 sum 刚好等于它自己的值
        if (root->left == nullptr && root->right == nullptr && sum == root->val) {
            return true;
        }

        // 把目标值减去当前节点的值，然后放任左右子树去穷举
        // 只要有一条路走得通 (||)，整条递归链就会直接返回 true
        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }

    // ==========================================
    // 解法 2：BFS 队列广搜 (队列打包记忆)
    // 时间 O(N)，空间 O(N) (最底层节点数量)
    // 防爆栈，适合极度倾斜的变态二叉树
    // ==========================================
    bool hasPathSumBFS(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;

        // pair<当前节点指针, 走到该节点时【尚未扣除该节点值】的剩余目标值>
        std::queue<std::pair<TreeNode*, int>> q;

        // 根节点入队，它的包袱就是最原始的 targetSum，还没扣自己的过路费
        q.push({root, targetSum});

        while (!q.empty()) {
            std::pair<TreeNode*, int> current = q.front();
            q.pop();

            TreeNode* node = current.first;
            // 获取当前节点需要面对的目标值 (包含当前节点自己的值)
            int remain_target = current.second;

            // 如果已经到了叶子节点，且它的值刚好等于这部分包袱，大功告成
            if (node->left == nullptr && node->right == nullptr && node->val == remain_target) {
                return true;
            }

            // 如果左孩子存在，把算好的、未来属于它的包袱打包传给它
            if (node->left != nullptr) {
                q.push({node->left, remain_target - node->val});
            }
            // 右孩子同理
            if (node->right != nullptr) {
                q.push({node->right, remain_target - node->val});
            }
        }

        return false;
    }
};

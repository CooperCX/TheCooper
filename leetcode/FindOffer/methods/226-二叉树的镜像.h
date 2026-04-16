/*
    翻转二叉树 (二叉树的镜像)
    Homebrew 作者被谷歌挂掉的“名题”
    核心逻辑：把每一个节点的左右子树进行指针呼唤
*/

#include <queue>
#include <utility>  // std::swap 需要的头文件

#include "../include/struct_define.h"

class MirrorTreeSolution {
   public:
    // ==========================================
    // 解法 1：DFS 递归深搜 (前序遍历法)
    // 优点：代码极度精简，3 行定乾坤
    // 时间复杂度 O(N)，空间复杂度 O(H)
    // ==========================================
    TreeNode* Mirror(TreeNode* pRoot) {
        // 【防御】触底条件：空节点没什么可翻转的
        if (pRoot == nullptr) return nullptr;

        // 1. 中：立刻交换当前节点的左、右孩子指针
        // (使用 std::swap 交换指针值，O(1) 极速操作)
        std::swap(pRoot->left, pRoot->right);

        // 2. 左：对（翻转后的）左子树下达全盘翻转命令
        Mirror(pRoot->left);
        // 3. 右：对（翻转后的）右子树下达全盘翻转命令
        Mirror(pRoot->right);

        // 收工，返回翻转完毕的自己
        return pRoot;
    }

    // ==========================================
    // 解法 2：BFS 队列广搜 (层序迭代法)
    // 优点：防爆栈，层层推进
    // 时间复杂度 O(N)，空间复杂度 O(N)
    // ==========================================
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // 把当前揪出来视察的这个节点的两个孩子换掉
            std::swap(node->left, node->right);

            // 把下一代丢进队列里，留给下几轮继续扒皮翻转
            // 注意：这里 push 的是谁先谁后无所谓，反正都要被治
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }

        return root;
    }
};

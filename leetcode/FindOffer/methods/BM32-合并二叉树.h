/*
    合并二叉树
    核心思想：同步的前序遍历 (中-左-右)
*/

#include "../include/struct_define.h"

class mergeTreesSolution {
   public:
    // 解法：DFS 递归合并 (基于修改原树)
    // 时间复杂度：O(min(N, M))，N和M分别是两棵树的节点数。因为只要有一边为空就直接返回，所以只遍历重叠部分！
    // 空间复杂度：O(min(H1, H2))，即重叠部分的树高（调用栈深度）
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        // ================= 【天然的短路合并机制】 =================
        // 只要有一棵树的当前节点为空，就直接返回另一棵树的当前节点（连同它底下的整个家族）。
        // 这一步直接将后续不必要的向下递归暴利“剪枝”了！
        if (root1 == nullptr) return root2;
        if (root2 == nullptr) return root1;

        // ================= 【前序遍历：处理“中”】 =================
        // 能走到这里，说明两个节点都真真切切地存在
        // 我们以 root1 为这片新天地的宿主，把 root2 的财产合并过来
        root1->val += root2->val;

        // ================= 【前序遍历：处理“左”和“右”】 =================
        // 把 root1 的左孩子 和 root2 的左孩子 送进同一个包厢继续谈判
        // 谈好的新左子树结果，依然由 root1 的左手牵着
        root1->left = mergeTrees(root1->left, root2->left);

        // 右边同理
        root1->right = mergeTrees(root1->right, root2->right);

        // 主节点 root1 带着已经吞并好的左膀右臂，向上给它的父节点交差
        return root1;
    }
};

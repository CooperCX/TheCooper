/*
    二叉树的最近公共祖先 (LCA)
    核心思想：自底向上的后序遍历，寻找左右子树反馈回来的“查人报告”
*/

#include "../include/struct_define.h"

class lowestCommonAncestorSolution {
   public:
    // 解法：递归式后序遍历 (Bottom-Up)
    // 时间复杂度：O(N) (最坏情况下，需要把整棵树每一个节点都搜一次)
    // 空间复杂度：O(H) (H 是树的高度，即递归调用的隐式栈空间)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // ================= 1. 递归终止条件与“抓人” =================
        // 如果到了空节点，说明这条路是个死胡同，给上级汇报“没找到”
        if (root == nullptr) return nullptr;

        // 如果我恰好就是 p 或者 q 中的一员，这叫做当场抓获！
        // 因为是从上往下找的，只要碰到了，根本不需要再往下找它的子树了，
        // （哪怕另一个节点躲在我的子树里，那我本人也天然是最近公共祖先！）
        if (root->val == p->val || root->val == q->val) return root;

        // ================= 2. 深入：派兵搜索左右区域 =================
        // (后序遍历：先深入最底层，然后逐渐向上级汇报)
        TreeNode* leftRes = lowestCommonAncestor(root->left, p, q);
        TreeNode* rightRes = lowestCommonAncestor(root->right, p, q);

        // ================= 3. 汇总：根据小弟汇报的情况定夺 =================
        // 如果左边的小弟空手而归，咱们的希望全在右小弟身上了。
        // 右小弟不管汇报上来的是具体的通缉犯，还是也是空手而归(nullptr)，我都如实上报！
        if (leftRes == nullptr) return rightRes;

        // 如果右边小弟空手而归，所有希望全在左小弟身上
        if (rightRes == nullptr) return leftRes;

        // 终极绝杀：左小弟和右小弟【都】抓到了逃犯！
        // 一个在我的左分支里，一个在我的右分支里。
        // 当且仅当这一步成立时，当前节点化身为真正劈开两人的那个枢纽 —— 【最近公共祖先】！
        // 于是我把我自己作为最终的答案，向上层层引荐。
        return root;
    }
};

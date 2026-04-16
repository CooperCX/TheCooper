/*
    二叉搜索树 (BST) 的最近公共祖先 (LCA)
    核心思想：利用 BST 左小右大的特性，寻找两点的“分岔口”
*/
#include "../include/struct_define.h"
class lowestCommonAncestorSolution {
   public:
    // 解法：借用 BST 特性的迭代法搜索
    // 优点：无需递归，无系统调用栈内存消耗
    // 时间复杂度：O(H)，H 为树高。每次迭代干掉一半的分支，类似于二分查找
    // 空间复杂度：O(1)，常数级指针应用
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 防御性判断
        if (root == nullptr) return nullptr;
        while (root != nullptr) {
            // 阶段 1：如果 p 和 q 的值【同时】小于当前节点
            // 说明它们俩抱团躲在左子树呢，咱们顺藤摸瓜往左走
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            }
            // 阶段 2：如果 p 和 q 的值【同时】大于当前节点
            // 说明它们俩抱团躲在右子树呢，咱们顺藤摸瓜往右走
            else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            }
            // 阶段 3：如果它们一左一右（或者其中一个干脆撞上了自己）
            // 说明这个节点就是它们分道扬镳的地方，也就是最近公共祖先！
            else {
                return root;
            }
        }
        // 理论上题目保证 p 和 q 都在树中，程序不会走到这一步
        return nullptr;
    }
};
/*
    判断平衡二叉树
    核心思想：自底向上的后序遍历，利用 -1 作为一票否决的短路信号牌
*/

#include <algorithm>  // 引入 std::abs 和 std::max

#include "../include/struct_define.h"

class IsBalancedSolution {
   public:
    // 解法：基于带状态剪枝的后续遍历，一次性求深度+辨真伪
    // 时间复杂度：O(N) (只遍历整棵树一次即出结果，绝不走回头路)
    // 空间复杂度：O(H) (H是树的高度，系统递归隐式栈空间)
    bool isBalanced(TreeNode* root) {
        // 只要最后收到的结果不是绝命信号 -1，就认为是平衡树
        return TreeDepth(root) != -1;
    }

   private:
    // 计算深度函数。如果某棵子树不平衡，直接“挟天子以令诸侯”，返回 -1 终止一切流程。
    int TreeDepth(TreeNode* root) {
        // 【防御】触底：空树深度天然是 0，且一定平衡
        if (root == nullptr) return 0;

        // ================= 后序遍历：自底向上判定 =================

        // 【左】：派人去左边丈量深度
        int leftDepth = TreeDepth(root->left);
        // 如果左边传来了绝命信号，自己不再费力去算右边了，果断跟风返回 -1，一层层抛上天庭
        if (-1 == leftDepth) return -1;

        // 【右】：派人去右边丈量深度
        int rightDepth = TreeDepth(root->right);
        // 如果右边出事了，同上，直接返回 -1 中断
        if (-1 == rightDepth) return -1;

        // 【中】：左右两国安然无恙，接下来就是审查两国国力差距了
        // 任何一边深出另一边超过 1 层，在此节点处产生不平衡裂痕
        if (std::abs(leftDepth - rightDepth) > 1) {
            return -1;  // 自己化身引发雪崩的一片雪花，向上抛出 -1
        }

        // 大哥，我和我的两位小弟全都平衡，请您拿着我们家族的最大深度去更上一层楼交差吧
        return std::max(leftDepth, rightDepth) + 1;
    }
};

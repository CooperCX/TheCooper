/*
    验证二叉搜索树 (BST)
    核心法则：BST 的中序遍历序列【必定】是严格单调递增的！
*/
#include <stack>

#include "../include/struct_define.h"
class isValidBSTSolution {
   public:
    // ==========================================
    // 解法 1：DFS 递归 (中序遍历法)
    // 优点：代码简洁优雅，利用指针对比避开下界值陷阱
    // 时间 O(N)，空间 O(H) (H为树深)
    // ==========================================
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = nullptr;  // 用于记录中序遍历序列中的“前驱节点”
        return InorderCheck(root, pre);
    }

   private:
    // 注意：pre 必须是指针的引用 (TreeNode*&)，确保全局只有一个 pre 在移动
    bool InorderCheck(TreeNode* root, TreeNode*& pre) {
        if (root == nullptr) return true;  // 空树天然是合法的
        // 1. 左：查验左子树。如果左子树里已经发现了假货，直接全盘否定
        if (!InorderCheck(root->left, pre)) return false;
        // 2. 中：对比当前节点与前驱节点的值
        // 这是整道题最核心的防线：BST要求严格递增，绝对不能出现前驱 >= 当前
        // (注意：普通二叉搜索树不允许存在相同值的节点，如果有需求，可以改写成 <)
        if (pre != nullptr && root->val <= pre->val) {
            return false;
        }

        // 【关键交接】当前节点审查合格，它自己荣升为新的“前驱”，去迎战下一个节点
        pre = root;
        // 3. 右：查验右子树
        return InorderCheck(root->right, pre);
    }

   public:
    // ==========================================
    // 解法 2：BFS 迭代 (中序遍历单栈法)
    // 优点：防超深递归爆栈，工业界首选
    // 复用通用的左、中、右出栈模板
    // ==========================================
    bool isValidBST2(TreeNode* root) {
        if (root == nullptr) return true;  // (你原代码这里是 false，虽然空树一般给 true，以题目要求为准即可)
        std::stack<TreeNode*> s;
        TreeNode* pre = nullptr;

        // curr 即原代码的 root
        TreeNode* curr = root;
        while (!s.empty() || curr != nullptr) {
            // 阶段 1：一路向左扎到底
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            // 阶段 2：终于触底，准备审问“中”节点
            curr = s.top();
            s.pop();
            // 核心审问环节：你这个节点，是不是比前一个访问过的节点小/相等？
            if (pre != nullptr && curr->val <= pre->val) {
                return false;  // 胆敢破坏递增规矩，立刻拖出去斩了
            }
            // 审问通过，自己变成前驱
            pre = curr;
            // 阶段 3：深入右边阵地
            curr = curr->right;
        }

        // 历经千辛万苦全部合情合理，这就是真货
        return true;
    }
};
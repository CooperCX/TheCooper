/*
将一个二叉搜索树转换为排序的双向链表
利用 BST 的中序遍历天然有序的特性
*/

#include <stack>

#include "../include/struct_define.h"

class convertBSTtoBiListSolution {
   public:
    // ===============================================
    // 解法 1：递归版中序遍历
    // 时间 O(N)，空间 O(H) (H 为递归栈深度)
    // ===============================================
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) return nullptr;

        TreeNode* pre = nullptr;   // 记录刚刚访问过的前一个节点
        TreeNode* head = nullptr;  // 记录双向链表的真正头节点（最小节点）

        // 开启中序遍历流水线
        ConvertCore(pRootOfTree, pre, head);

        return head;  // 全局遍历完后，head 就是我们要的答案
    }

   private:
    // 【高阶 C++ 素质】千万注意：pre 和 head 必须是指针的引用 (TreeNode*&)！
    // 否则在子递归里修改的指针指向，根本无法同步反馈给上层调用者！
    void ConvertCore(TreeNode* root, TreeNode*& pre, TreeNode*& head) {
        if (root == nullptr) return;

        // 1. 左：一直向左深入，把比自己小的安排好
        ConvertCore(root->left, pre, head);

        // 2. 中：处理当前节点的双向连接
        if (pre != nullptr) {
            // 如果前面有节点，建立双向连接
            pre->right = root;  // 前面的节点的 next（也就是右指针）挂在当前身上
            root->left = pre;   // 当前节点的 prev（也就是左指针）挂在前面身上
        } else {
            // 如果前面根本没有节点，说明当前节点是中序遍历遇到的第 1 个节点！
            // 它绝对是整棵树里最小的元素，立刻把它封为头节点！
            head = root;
        }

        // 当前节点处理结束，交接接力棒！它自己光荣地成为了“前驱”
        pre = root;

        // 3. 右：向右去去安排比自己大的节点
        ConvertCore(root->right, pre, head);
    }

   public:
    // ===============================================
    // 解法 2：迭代版中序遍历 (借助标准栈)
    // 算法思想同上，复用了前几题我们写好的中序双 while 模板
    // ===============================================
    TreeNode* ConvertDFS(TreeNode* pRootOfTree) {
        // 其实这里叫 ConvertByIter 或者 ConvertByStack 更贴切，DFS 通常指代递归
        if (pRootOfTree == nullptr) return nullptr;

        std::stack<TreeNode*> s;
        TreeNode* pre = nullptr;
        TreeNode* head = nullptr;

        // 探路员指针
        TreeNode* curr = pRootOfTree;

        while (!s.empty() || curr != nullptr) {
            // 阶段 1：疯狂往左扎，把一路上的节点全都当作未来要处理的“中”雪藏在栈里
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            // 阶段 2：左边终于没路了，开始出栈处理（这就是“中”）
            curr = s.top();
            s.pop();

            // === 【核心连接逻辑：替换掉了打印操作】 ===
            if (pre != nullptr) {
                pre->right = curr;
                curr->left = pre;
            } else {
                head = curr;
            }
            // 交接接力棒
            pre = curr;
            // =========================================

            // 阶段 3：探路员去右边探索
            curr = curr->right;
        }

        return head;
    }
};

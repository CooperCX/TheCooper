#include <queue>

#include "../include/struct_define.h"
class isSymmetricalSolution {
   public:
    bool isSymmetrical(TreeNode* pRoot) {
        if (pRoot == nullptr) return true;
        return isMirror(pRoot->left, pRoot->right);
    }

    // BFS 迭代解法：不怕树有多深，只看内存够不够
    bool isSymmetric(TreeNode* pRoot) {
        if (pRoot == nullptr) return true;
        std::queue<TreeNode*> q;
        // 把根节点的左右子节点送入队列
        q.push(pRoot->left);
        q.push(pRoot->right);
        while (!q.empty()) {
            // 每次从队列中拿两个应该对称的节点出来比较
            TreeNode* leftNode = q.front();
            q.pop();
            TreeNode* rightNode = q.front();
            q.pop();
            // 如果都为空，说明这一分支对称抵达叶子底端，继续检查队列中的其他节点
            if (leftNode == nullptr && rightNode == nullptr) continue;

            // 如果一个为空另一个不为空，或者值不相等，直接判定不对称
            if (leftNode == nullptr || rightNode == nullptr || leftNode->val != rightNode->val) {
                return false;
            }
            // 按镜像要求推入下一层子节点（注意入队顺序！）
            q.push(leftNode->left);    // 左节点的左孩子
            q.push(rightNode->right);  // 对标 右节点的右孩子

            q.push(leftNode->right);  // 左节点的右孩子
            q.push(rightNode->left);  // 对标 右节点的左孩子
        }
        return true;
    }

   private:
    bool isMirror(TreeNode* leftNode, TreeNode* rightNode) {
        if (!leftNode && !rightNode) return true;
        if (!leftNode || !rightNode || leftNode->val != rightNode->val) return false;

        return isMirror(leftNode->left, rightNode->right) && isMirror(leftNode->right, rightNode->left);
    }
};
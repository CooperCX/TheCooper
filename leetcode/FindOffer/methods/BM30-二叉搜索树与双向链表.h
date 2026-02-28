/*
将一个二叉搜索树转换为排序的双向链表
1. 中序遍历二叉树，再转换为双向列表
2. 递归做法
*/

#include <stack>
#include <vector>

#include "../include/struct_define.h"

class convertBSTtoBiListSolution {
   public:
    /*递归做法*/
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) return nullptr;

        TreeNode *pre = nullptr, *head = nullptr;
        ConvcertCore(pRootOfTree, pre, head);

        return head;
    }

    void ConvcertCore(TreeNode* root, TreeNode*& pre, TreeNode*& head) {
        if (!root) return;

        ConvcertCore(root->left, pre, head);

        if (pre) {
            pre->right = root;
            root->left = pre;
        } else {
            head = root;
        }
        pre = root;

        ConvcertCore(root->right, pre, head);
    }

    /*中序遍历*/
    TreeNode* ConvertDFS(TreeNode* pRootOfTree) {
        if (!pRootOfTree) return nullptr;

        std::stack<TreeNode*> s;
        TreeNode *pre = nullptr, *head = nullptr;
        while (!s.empty() || pRootOfTree) {
            while (pRootOfTree) {
                s.push(pRootOfTree);
                pRootOfTree = pRootOfTree->left;
            }

            pRootOfTree = s.top();
            s.pop();

            if (pre) {
                pre->right = pRootOfTree;
                pRootOfTree->left = pre;
            } else {
                head = pRootOfTree;
            }

            pre = pRootOfTree;
            pRootOfTree = pRootOfTree->right;
        }

        return head;
    }
};
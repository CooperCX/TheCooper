/*
将一个二叉搜索树转换为排序的双向链表
1. 中序遍历二叉树，再转换为双向列表
2. 递归做法
*/

#include <vector>
#include <stack>
#include "struct_define.h"

class Solution {
public:
    /*中序遍历*/
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) {
            return nullptr;
        }
        std::vector<TreeNode*> results;
        ConvertToVector(pRootOfTree, results);
        return ConvertToBiList(results);
    }

    /*递归做法*/
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr) {
            return nullptr;
        }
        std::stack<TreeNode*> s;

        TreeNode* head = nullptr, * pre = nullptr;
        while (!s.empty() || pRootOfTree) {
            while (pRootOfTree) {
                s. push(pRootOfTree);
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

private:
    void ConvertToVector(TreeNode* pRootOfTree, std::vector<TreeNode*>& results) {
        if (pRootOfTree == nullptr) {
            return;
        }
        if (pRootOfTree) {
            if (pRootOfTree->left) {
                ConvertToVector(pRootOfTree->left, results);
            }
            results.push_back(pRootOfTree);
            if (pRootOfTree->right) {
                ConvertToVector(pRootOfTree->right,results);
            }
        }
    }
    std::vector<TreeNode*> ConvertToVector(TreeNode* pRootOfTree) {
        std::vector<TreeNode*> results;
        if (pRootOfTree == nullptr) {
            return results;
        }
        std::stack<TreeNode*> s;
        while (!s.empty() || pRootOfTree) {
            while (pRootOfTree) {
                s.push(pRootOfTree);
                pRootOfTree = pRootOfTree->left;
            }
            TreeNode* node = s.top();
            results.push_back(node);
            s.pop();
            if (node->right) {
                pRootOfTree = node->right;
            }
        }
        return results;
    }

    TreeNode* ConvertToBiList(const std::vector<TreeNode*>& results) {
        if (results.empty()) {
            return nullptr;
        }
        for (auto i = 0; i < results.size() - 1; i++) {
            results[i]->right = results[i + 1];
            results[i + 1]->left = results[i];
        }
        return results[0];
    }
};
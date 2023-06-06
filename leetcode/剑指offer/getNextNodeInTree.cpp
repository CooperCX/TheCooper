#include "struct_define.h"

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (pNode == nullptr) {
            return nullptr;
        }
        if (pNode->right) {
            pNode = pNode->right;
            while (pNode->left) {
                pNode = pNode->left;
            }
            return pNode;
        }
        while (pNode->next) {
            TreeLinkNode* proot = pNode->next;
            if (proot->left == pNode) {
                return proot;
            }
            pNode = pNode->next;
        }
        return nullptr;
    }
};
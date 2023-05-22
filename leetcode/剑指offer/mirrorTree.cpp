#include "struct_define.h"

class MirrorTree {
public:
    TreeNode* Mirror(TreeNode* pRoot) {
        MirrorCore(pRoot);
        return pRoot;
    }
private:
    void MirrorCore(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return;
        }
        TreeNode* pTemp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = pTemp;
        MirrorCore(pRoot->left);
        MirrorCore(pRoot->right);
    }
};
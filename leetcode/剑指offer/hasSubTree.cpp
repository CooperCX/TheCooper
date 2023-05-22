#include "struct_define.h"

/*思路：一般树的问题都是用迭代解决
    在A树的子树中找到是否存在B树，需要两个步骤：
    1. 遍历A树的节点，是否等于B树的根节点
    2. 判断B树是不是从A树某个节点开始的子树
*/
class Solution {
public:
    /*1. 遍历A树的节点，是否等于B树的根节点*/
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        if (pRoot1 == nullptr || pRoot2 == nullptr) {
            return false;
        }
        return HasSubTreeCore(pRoot1, pRoot2) ||
            HasSubtree(pRoot1->left, pRoot2) ||
            HasSubtree(pRoot1->right, pRoot2);
    }
private:
    /*2. 判断B树是不是从A树某个节点开始的子树*/
    bool HasSubTreeCore(TreeNode* pRoot1, TreeNode* pRoot2) {
        /*迭代终止条件*/
        if (pRoot2 == nullptr) {
            return true;
        }
        if (pRoot1 == nullptr) {
            return false;
        }
        /*根节点匹配，进入判断左右节点是否匹配*/
        if (pRoot1->val == pRoot2->val) {
            return HasSubTreeCore(pRoot1->left, pRoot2->left) && HasSubTreeCore(pRoot1->right, pRoot2->right);
        } else {
            return false;
        }
    }
};
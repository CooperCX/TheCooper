/*二叉搜索树(Bi-search-Tree, BST)：左子树的所有节点都小于根节点，右子树的所有节点都大于根节点*/

#include <vector>
#include "struct_define.h"


class Solution {
public:
    bool VerifySquenceOfBST(std::vector<int> sequence) {
        int n = sequence.size();
        if (n == 0) {
            return false;
        } else if (n == 1) {
            return true;
        } else {
            return VerifySquenceOfBSTCore(sequence, 0, n - 1);
        }
    }
private:
    bool VerifySquenceOfBSTCore(std::vector<int> sequence, int start, int end) {
        if (start >= end) {
            return true;
        }
        int low = start;
        while (low < end && sequence[low] < sequence[end]) {
            low++;
        }
        for (int i = low; i < end; i++) {
            if (sequence[i] <= sequence[end]) {
                return false;
            }
        }
        return VerifySquenceOfBSTCore(sequence, start, low - 1) &&
            VerifySquenceOfBSTCore(sequence, low, end - 1);
    }
};
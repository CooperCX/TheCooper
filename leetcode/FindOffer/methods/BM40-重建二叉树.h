/*
    根据前序和中序遍历重建二叉树
    前序提供“谁是根节点”，中序提供“树的分界线”
*/
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "../include/struct_define.h"
class reConstructBinaryTreeSolution {
   public:
    // 解法：哈希表优化的坐标偏移递归法
    // 时间复杂度：O(N) (哈希表查询 O(1)，每个节点建立一次)
    // 空间复杂度：O(N) (哈希表占用 O(N) 空间，递归树高平均 O(logN))
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        // 【防御】如果给的数组是空的，或者两者大小不一致（数据损坏），直接拒收
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) {
            return nullptr;
        }
        // ================= 【性能核心：哈希索引预处理】 =================
        // 为了避免在递归中每次都要用 for 循环去 inorder 里寻找 root 节点的位置，
        // 我们提前一次性把 inorder 里的 (节点值 -> 索引) 映射缓存进哈希字典。
        // （前提：本题默认树中没有重复的值）
        std::unordered_map<int, int> inorder_map;
        for (int i = 0; i < inorder.size(); i++) {
            inorder_map[inorder[i]] = i;
        }
        return reConstructBinaryTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inorder_map);
    }

   private:
    TreeNode* reConstructBinaryTree(const std::vector<int>& preorder, int pre_left, int pre_right,
                                    const std::vector<int>& inorder, int vin_left, int vin_right,
                                    const std::unordered_map<int, int>& inorder_map) {
        // 递归终止条件：当左边界越过右边界，说明这个小阵营被榨干了，没有人了，返回空指针
        if (pre_left > pre_right) return nullptr;
        // 【破题第一步】：前序遍历序列的开路先锋 (pre_left) 绝对是当前这一片树的根！
        int root_val = preorder[pre_left];
        TreeNode* root = new TreeNode(root_val);
        // 【破题第二步】：去中序遍历里找到这一刀应该切在哪里 (O(1) 极速下刀)
        int root_index_in_inorder = inorder_map.at(root_val);

        // 【破题第三步】：算出这一刀切出来后，左边阵营究竟分到了多少个人？
        int left_tree_size = root_index_in_inorder - vin_left;
        // 【破题第四步】：化身司令，把前序和中序两张大饼切出去，分别下放给左小弟和右小弟

        // 分配给左小弟的地盘：
        // 前序地盘：[前序起点+1, 前序起点+左兵力数] （把当前 root 去掉后，紧跟在后面的 left_tree_size 个人）
        // 中序地盘：[中序起点, 切割点-1] （切割刀痕左边的所有人）
        root->left = reConstructBinaryTree(preorder, pre_left + 1, pre_left + left_tree_size, inorder, vin_left,
                                           root_index_in_inorder - 1, inorder_map);

        // 分配给右小弟的地盘：
        // 前序地盘：[前序起点+左兵力数+1, 前序终点] （前序数组里，左小弟拿剩下的部分全归你）
        // 中序地盘：[切割点+1, 中序终点] （切割刀痕右边的所有人）
        root->right = reConstructBinaryTree(preorder, pre_left + left_tree_size + 1, pre_right, inorder,
                                            root_index_in_inorder + 1, vin_right, inorder_map);
        return root;
    }
};
/*
    二叉树的序列化与反序列化
    核心法则：带空指针标记的前序遍历
    节点之间用 '!' 分隔，空指针用 '#' 标记
*/
#include <string>

#include "../include/struct_define.h"
class SerializeTreeSolution {
   public:
    // ==========================================
    // 序列化：树 -> 字符串
    // 时间 O(N)，空间 O(N) (递归栈与字符串开销)
    // ==========================================
    std::string serialize(TreeNode* root) {
        // 如果当前节点为空，返回空标记 '#' 和 分隔符 '!'
        if (root == nullptr) {
            return "#!";
        }
        // 前序遍历：中 -> 左 -> 右
        // 1. 记录当前节点的值，挂上分隔符 '!'
        std::string str = std::to_string(root->val) + "!";

        // 2. 缝合左子树的序列化结果
        str += serialize(root->left);

        // 3. 缝合右子树的序列化结果
        str += serialize(root->right);
        return str;
    }
    // ==========================================
    // 反序列化：字符串 -> 树
    // ==========================================
    TreeNode* deserialize(std::string data) {
        if (data.empty()) return nullptr;
        // 全局读取指针，记录当前解析到了字符串的哪个位置
        // 传引用是反序列化的灵魂，保证递归上下层进度一致！
        int idx = 0;
        return deserializeCore(data, idx);
    }

   private:
    TreeNode* deserializeCore(const std::string& data, int& idx) {
        // 【防御】安全边界检查
        if (idx >= data.size()) return nullptr;
        // 1. 探根求源：如果当前碰到了 '#'，说明到了空节点
        if (data[idx] == '#') {
            idx += 2;  // '#' 占一位，它背后的分隔符 '!' 占一位，一共跳 2 步
            return nullptr;
        }
        // 2. 解析数字 (C++ 字符串转数字的高频核心功底)
        int num = 0;
        bool is_negative = false;
        // 处理负号
        if (data[idx] == '-') {
            is_negative = true;
            idx++;
        }
        // 剥离字符计算数字，直到遇到分隔符 '!' (意味着一个块读完了)
        while (idx < data.size() && data[idx] != '!') {
            num = num * 10 + (data[idx] - '0');
            idx++;
        }
        // 负号赋予生效
        if (is_negative) num = -num;
        // 跳过这个数字块最后的分隔符 '!'，为下一次递归对齐下标
        idx++;
        // 3. 伟大的重建工程 (前序遍历逆操作)
        // 第一时间建立当前的主干节点
        TreeNode* node = new TreeNode(num);

        // 分配任务：左子树吃掉属于它的字符串并把 idx 在内部推移
        node->left = deserializeCore(data, idx);

        // 剩下的字符串，就是右子树的口粮
        node->right = deserializeCore(data, idx);
        return node;
    }
};
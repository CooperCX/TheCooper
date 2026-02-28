#include <string>

#include "../include/struct_define.h"

class SerializeTreeSolution {
   public:
    // Encodes a tree to a single string.
    std::string serialize(TreeNode* root) {
        std::string str;
        if (!root) {
            str += "#!";
            return str;
        }

        str += std::to_string(root->val) + "!";
        str += serialize(root->left);
        str += serialize(root->right);

        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(std::string data) {
        if (data.empty()) return nullptr;

        int idx = 0;
        return deserializeCore(data, idx);
    }

    TreeNode* deserializeCore(const std::string& data, int& idx) {
        if (idx >= data.size()) return nullptr;

        if ('#' == data[idx]) {
            idx += 2;
            return nullptr;
        }

        int num = 0;
        bool is_negative = false;

        if (data[idx] == '-') {
            is_negative = true;
            idx++;
        }

        while (idx < data.size() && data[idx] != '!') {
            num = num * 10 + (data[idx] - '0');
            idx++;
        }

        if (is_negative) num = -num;

        idx++;

        TreeNode* node = new TreeNode(num);
        node->left = deserializeCore(data, idx);
        node->right = deserializeCore(data, idx);

        return node;
    }
};
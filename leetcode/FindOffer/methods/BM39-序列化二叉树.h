#include "../include/struct_define.h"
#include <string>

class SerializeTreeSolution {
public:
    char* Serialize(TreeNode* root) {
        std::string str = SerializeCore(root);
        char* res = new char[str.length()];
        for (int i = 0; i < str.length(); i++) {
            res[i] = str[i];
        }
        return res;
    }

    std::string SerializeCore(TreeNode* root) {
        std::string str = "";
        if (root == nullptr) {
            str += "#!";
            return str;
        }
        str += (std::to_string(root->val) + "!");
        str += SerializeCore(root->left);
        str += SerializeCore(root->right);
        return str;
    }

    TreeNode* Deserialize(char* str) {
        return DeserializeCore(str);
    }

    TreeNode* DeserializeCore(char*& str) {
        if (*str == '#') {
            str++;
            return nullptr;
        }
        int num = 0;
        while (*str != '!') {
            num = num * 10 + (*str - '0');
            str++;
        }
        TreeNode* root = new TreeNode(num);
        root->left = DeserializeCore(++str);
        root->right = DeserializeCore(++str);

        return root;
    }
};
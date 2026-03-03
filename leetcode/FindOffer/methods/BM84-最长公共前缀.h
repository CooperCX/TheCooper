#include <string>
#include <vector>

class Solution {
   public:
    // 【规范】使用 const 引用，避免拷贝整个字符串数组
    std::string longestCommonPrefix(const std::vector<std::string>& strs) {
        if (strs.empty()) {
            return "";
        }
        // 纵向扫描：以第一个字符串为基准，遍历它的每一列(每一个字符)
        for (int j = 0; j < strs[0].length(); ++j) {
            char c = strs[0][j];

            // 遍历其余所有的字符串，看它们在当前这一列(j) 是不是也是字符 c
            for (int i = 1; i < strs.size(); ++i) {
                // 【极其关键】必须把长度上限检查 (j == strs[i].length()) 写在前面！
                // 利用 || 的短路特性，一旦发现这个短字符串已经到底了，
                // 后面的 strs[i][j] 就根本不会被执行，从而完美避开越界崩溃！
                if (j == strs[i].length() || strs[i][j] != c) {
                    // 返回第一个字符串从 0 开始，长度为 j 的子串
                    return strs[0].substr(0, j);
                }
            }
        }

        // 如果能完整地把第一个字符串全部遍历完都没有 return，
        // 说明第一个字符串就是最短的木板，它自己就是最长公共前缀。
        return strs[0];
    }
};
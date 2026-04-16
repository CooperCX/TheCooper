/*输出字符串的全排序*/

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class StringPermutationSolution {
   public:
    std::vector<std::string> results;

   public:
    //  使用标准库函数next_permutation
    std::vector<std::string> Permutation(std::string str) {
        std::sort(str.begin(), str.end());
        do {
            results.push_back(str);
        } while (std::next_permutation(str.begin(), str.end()));
        return results;
    }

    // 解法二：标准回溯法 (面试官通常会要求你手写这个)
    std::vector<std::string> permutationByBacktrack(std::string str) {
        std::vector<std::string> results;
        if (str.empty()) return results;
        std::string current_path = "";
        std::vector<bool> used(str.length(), false);  // 极其高效的访问标记数组
        // 【致命修复】必须针对字符串本身进行排序，让相同字符相邻，才能做树层去重！
        std::sort(str.begin(), str.end());
        backtrack(str, used, current_path, results);

        return results;
    }

   private:
    // 【致命修复】必须使用 const std::string& 避免递归中发生海量的字符串深拷贝
    void backtrack(const std::string& str, std::vector<bool>& used, std::string& current_path,
                   std::vector<std::string>& results) {
        // 1. 递归终止条件
        if (current_path.length() == str.length()) {
            results.push_back(current_path);
            return;
        }
        // 2. 遍历做选择
        for (int i = 0; i < str.length(); ++i) {
            // 如果已经被使用过，跳过
            if (used[i]) {
                continue;
            }
            // 【经典去重剪枝】：避免在同一位置放下相同的字符
            // 如果当前字符等于前一个字符，且前一个字符刚刚在这一层被撤销使用 (!used[i - 1])
            if (i > 0 && str[i] == str[i - 1] && !used[i - 1]) {
                continue;
            }
            // 3. 做出选择
            current_path.push_back(str[i]);
            used[i] = true;
            // 4. 递归下探
            backtrack(str, used, current_path, results);
            // 5. 撤销选择 (回溯现场)
            used[i] = false;
            current_path.pop_back();
        }
    }
};
/*输出字符串的全排序*/

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

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

    // 使用递归解法
    std::vector<std::string> Permutation(const std::string& str) {
        std::unordered_map<int, bool> vis;
        std::string temp = "";
        std::vector<std::string> results;

        PermuteString(str, vis, temp, results);
        return results;

    }
private:
    void PermuteString(std::string str,
                       std::unordered_map<int, bool>& vis,
                       std::string& temp,
                       std::vector<std::string>& res)
    {
        if (temp.length() == str.length()) {
            res.push_back(temp);
            return;
        }
        for (int i = 0; i < str.length(); i++) {
            if (vis[i]) {
                continue;
            }
            if (i > 0 && str[i] == str[i - 1] && !vis[i - 1]) {
                continue;
            }
            temp += str[i];
            vis[i] = true;
            PermuteString(str, vis, temp, res);
            temp.pop_back();
            vis[i] = false;
        }
    }
};
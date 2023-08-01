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
        int n = str.length();
        if (n == 0) {
            results.push_back(str);
            return results;
        }
        PermutationCore(str, 0, n - 1);
        return results;
    }
private:
    void PermutationCore(std::string str, int begin, int end) {
        if (begin == end) {
            results.push_back(str);
            return;
        }
        std::unordered_map<char, bool> visited;
        for (int i = begin; i <= end; i++) {
            if (visited[str[i]]) {
                continue;
            }
            std::swap(str[i], str[begin]);
            PermutationCore(str, begin + 1, end);
            std::swap(str[i], str[begin]);
            visited[str[i]] = true;
        }
    }
};
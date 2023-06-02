#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int FirstNotRepeatingChar(std::string str) {
        int n = str.length();

        std::unordered_map<char, int> ump;
        for (int i = 0; i < n; i++) {
            ump[str[i]]++;
        }
        for (int i = 0; i < n; i++) {
            if (ump[str[i]] == 1) {
                return i;
            }
        }
        return -1;
    }

    // 自己写的方法
    int FirstNotRepeatingChar(std::string str) {
        int n = str.length();

        std::vector<int> visited;
        for (int i = 0; i < n; i++) {
            if (std::find(visited.begin(), visited.end(), i) != visited.end()) {
                continue;
            }
            bool once = true;
            for (int j = i + 1; j < n; j++) {
                if (str[j] == str[i]) {
                    visited.push_back(j);
                    once = false;
                }
            }
            if (once) {
                return i;
            }
        }
        return -1;
    }
};
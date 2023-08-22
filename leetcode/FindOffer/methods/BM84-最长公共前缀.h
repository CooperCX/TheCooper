#include <vector>
#include <string>

class Solution {
public:

    std::string longestCommonPrefix(std::vector<std::string>& strs) {
        int n = strs.size();
        if (n == 0) {
            return "";
        }
        for (int j = 0; j < strs[0].length(); j++) {
            for (int i = 1; i < n; i++) {
                if (strs[i][j] != strs[0][j] || j == strs[i].length()) {
                    return strs[0].substr(0, j);
                }
            }
        }
        return strs[0];
    }
};
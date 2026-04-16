#include <algorithm>
#include <stack>
#include <string>

inline int longestValidParentheses(std::string s) {
    if (s.empty()) return 0;

    std::stack<int> indices;
    indices.push(-1);
    int maxLen = 0;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            indices.push(i);
        }

        if (s[i] == ')') {
            indices.pop();
            if (indices.empty()) {
                indices.push(i);
            } else {
                maxLen = std::max(maxLen, i - indices.top());
            }
        }
    }

    return maxLen;
}
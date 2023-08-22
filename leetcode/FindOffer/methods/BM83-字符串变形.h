#include <string>
#include <stack>

class StirngTransSolution {
public:

    std::string trans(std::string s, int n) {
        std::stack<std::string> stack;
        int pre = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] != ' ') {
                if (s[i] >= 'A' && s[i] <= 'Z') {
                    s[i] += 32;
                } else if (s[i] >= 'a' && s[i] <= 'z') {
                    s[i] -= 32;
                }
            } else {
                stack.push(std::string(s.begin() + pre, s.begin() + i));
                stack.push(" ");
                pre = i + 1;
            }
            if(i == n - 1) {
                stack.push(std::string(s.begin() + pre, s.end()));
            }
        }
        std::string res;
        while (!stack.empty()) {
            res += stack.top();
            stack.pop();
        }
        return res;
    }
};
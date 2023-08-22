#include <vector>
#include <string>
#include <stack>

class ExprSolution {
public:

    int solve(std::string s) {
        return function(s, 0)[0];
    }

    std::vector<int> function(std::string s, int index) {
        std::stack<int> stack;
        int num = 0;
        char op = '+';
        int i;

        for (i = index; i < s.length(); i++) {
            if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                if (i != s.length() - 1) {
                    continue;
                }
            }
            if (s[i] == '(') {
                num = function(s, i + 1)[0];
                i = function(s, i + 1)[1];
                if (i != s.length() - 1) {
                    continue;
                }
            }
            switch (op) {
            case '+':
                stack.push(num);
                break;
            case '-':
                stack.push(-num);
                break;
            case '*':
                int temp = stack.top();
                stack.pop();
                stack.push(temp * num);
                break;
            }
            num = 0;
            if (s[i] == ')') {
                break;
            } else {
                op = s[i];
            }
        }
        int sum = 0;
        while (!stack.empty()) {
            sum += stack.top();
            stack.pop();
        }
        return std::vector<int> {sum, i};
    }
};
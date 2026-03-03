#include <stack>
#include <string>
#include <vector>

class ExprSolution {
   public:
    int solve(std::string s) {
        int index = 0;
        return compute(s, index);
    }

    int compute(const std::string& s, int& i) {
        long long num = 0;
        char op = '+';
        std::stack<int> sum;

        while (i < s.length()) {
            char c = s[i++];
            if (isdigit(c)) num = num * 10 + (c - '0');

            if (c == '(') {
                num = compute(s, i);
            }

            if ((!isdigit(c) && c != ' ') || i == s.length()) {
                switch (op) {
                    case '+':
                        sum.push(num);
                        break;
                    case '-':
                        sum.push(-num);
                        break;
                    case '*': {
                        int temp = sum.top();
                        sum.pop();
                        sum.push(temp * num);
                        break;
                    }
                }

                num = 0;
                op = c;

                if (c == ')') break;
            }
        }

        int res = 0;
        while (!sum.empty()) {
            res += sum.top();
            sum.pop();
        }

        return res;
    }
};
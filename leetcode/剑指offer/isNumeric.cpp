/*
字符串是否表示数值
条件：
1. 除了'0'~'9', '.', '-', '+', 'e', 'E'其他都是不符合的
2. 'e'和'E'只能有一个，且后面必须有数字
3. '.'只能出现一次，且不能在开头或者'e'和'E'的后面
4. '+'和'-'第一次出现如果不在开头，就必须在'e'和'E'的后面，第二次出现必须在'e'和'E'的后面
*/

#include <string>

class Solution {
public:
    bool isNumeric(std::string str) {
        bool hasE = false, signal = false, decimal = false;
        int n = str.length();
        for (int i = 0; i < n; i++) {
            if (str[i] == 'e' || str[i] == 'E') {
                if (i >= n - 1 || hasE) {
                    return false;
                }
                hasE = true;
            } else if (str[i] == '.') {
                if (i == 0 || decimal || hasE) {
                    return false;
                }
                decimal = true;
            } else if (str[i] == '+' || str[i] == '-') {
                if (!signal && i > 0 && str[i - 1] != 'e' && str[i - 1] != 'E') {
                    return false;
                }
                if (signal&& str[i - 1] != 'e' && str[i - 1] != 'E') {
                    return false;
                }
                signal = true;
            } else if (str[i] < '0' || str[i] > '9') {
                return false;
            } else {
                continue;
            }
        }
        return true;
    }
};
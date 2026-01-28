#include <climits>
#include <string>

/* 丢弃前导空格：跳过字符串开头的空白字符。
处理符号：检查第一个非空字符是否为 '+' 或 '-'，确定结果的正负。
数字转换：读取后续数字字符，直到遇到非数字字符或到达末尾。
溢出处理：如果转换后的结果超出了 int 的表示范围（INT_MIN 到 INT_MAX），则根据规则返回最大值或最小值。 */

class AtoiSolution {
   public:
    int atoi(std::string str) {
        if (str.empty()) {
            return 0;
        }
        int i = 0;
        int n = str.length();
        long long res = 0;
        int sign = 1;

        while (i < n && ' ' == str[i]) {
            i++;
        }

        if (i < n && ('+' == str[i] || '-' == str[i])) {
            sign = ('-' == str[i]) ? -1 : 1;
            i++;
        }

        for (; i < n; i++) {
            if (str[i] > '9' || str[i] < '0') {
                break;
            }
            res = res * 10 + (str[i] - '0');
            if (1 == sign && res > INT_MAX) return INT_MAX;
            if (-1 == sign && -res < INT_MIN) return INT_MIN;
        }

        return static_cast<int>(res * sign);
    }
};
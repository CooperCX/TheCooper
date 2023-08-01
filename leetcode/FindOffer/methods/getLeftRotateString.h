#include <string>

class getLeftRotateStringSolution {
public:
    // 巧妙substr()方法
    std::string LeftRotateString(std::string str, int k) {
        int n = str.length();
        if (n == 0) {
            return str;
        }
        if (k > n) {
            k = k % n;
        }
        str += str;
        return str.substr(k, n);
    }

    //  循环k次
    std::string LeftRotateString(std::string str, int k) {
        int n = str.length();
        if (n == 0) {
            return str;
        }
        while (k > 0) {
            char c = str[0];
            for (int i = 0; i < n - 1; i++) {
                str[i] = str[i + 1];
            }
            str[n - 1] = c;
            k--;
        }
        return str;
    }
};
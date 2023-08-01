#include <string>

class atoiSolution {
public:
    int atoi(std::string str) {
        int n = str.length();
        if (n == 0) {
            return 0;
        }
        int i = 0, flag = 1, isSignal = 0;
        while (i < n && str[i] == ' ') {
            i++;
        }
        if (i >= n) {
            return 0;
        }
        while (i < n && str[i] == '-' || str[i] == '+') {
            if (str[i] == '-') {
                flag = -1;
            }
            i++;
            isSignal++;
            if (isSignal > 1) {
                return 0;
            }
        }
        int res = 0;
        for (; i < n; i++) {
            if (str[i] < '0' || str[i] > '9') {
                return 0;
            }
            res = res * 10 + str[i] - '0';
            if (res > INT_MAX && flag == 1) {
                return 0;
            }
            if (res - 1 > INT_MAX && flag == -1) {
                return 0;
            }
        }
        return flag * res;
    }
};
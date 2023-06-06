#include <vector>

class Solution {
public:
    // 找规律做法
    int cutRope(int number) {
        if (number < 2) {
            return 0;
        }
        if (number < 4) {
            return number - 1;
        }
        int res = 1;
        while (number > 4) {
            res *= 3;
            number -= 3;
        }
        res *= number;
        return res;
    }

    // dp[i]表示：绳子长度为i时，得到的最大乘积
    int cutRope(int number) {
        if (number < 2) {
            return 0;
        }
        if (number < 4) {
            return number - 1;
        }
        int res = 0;
        std::vector<int> temp(number + 1, 0);
        temp[1] = 1;
        temp[2] = 2;
        temp[3] = 3;
        for (int i = 4; i <= number; i++) {
            for (int j = 1; j <= i / 2; j++) {
                res = std::max(res, temp[j] * temp[i - j]);
                temp[i] = res;
            }
        }
        return temp[number];
    }
};
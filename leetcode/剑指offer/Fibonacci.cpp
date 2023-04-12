// 动态规划
class Solution {
public:
    int Fibonacci(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        int f = 1, s = 1, t = 0;
        for (int i = 3; i <= n; i++) {
            t = f + s;
            f = s;
            s = t;
        }
        return t;
    }
};
class PowerSolution {
   public:
    double Power(double base, int exponent) {
        // 【防御性编程核心】：立刻用 long long 接管有符号 int，防止取反时越界
        long long exp = exponent;

        if (exp < 0) {
            base = 1.0 / base;  // 底数倒过来
            exp = -exp;         // 此时取反绝对安全
        }

        double res = 1.0;

        // 【快速幂核心逻辑】
        while (exp > 0) {
            // 如果当前二进制的最后一位是 1，把当前的底数乘进结果里
            if (exp & 1) {
                res *= base;
            }
            // 底数自身平方翻倍 (即 x -> x^2 -> x^4 -> x^8 ...)
            base *= base;
            // 指数右移一位，探查下一位二进制
            exp >>= 1;
        }

        return res;
    }
};

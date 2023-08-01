
// 快速幂运算
class PowerSolution {
public:
    double Power(double base, int exponent) {
        if (exponent < 0) {
            base = 1 / base;
            exponent  = -exponent;
        }
        double res = 1.0;
        while (exponent) {
            if (exponent & 1) {
                res *= base;
            }
            base *= base;
            exponent >>= 1;
        }
        return res;
    }
};
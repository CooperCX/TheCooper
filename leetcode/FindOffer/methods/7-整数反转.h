#include <climits>  // 引入 INT_MAX 和 INT_MIN

class reverseIntSolution {
   public:
    int reverseInt(int num) {
        int res = 0;

        // 兼容负数
        while (num != 0) {
            // 获取末尾一位数字
            int pop = num % 10;
            num /= 10;

            // ============ 溢出提前拦截机制 ============
            // 预判正数溢出风险
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && pop > 7)) {
                return 0;  // 题目要求溢出时返回 0
            }
            // 预判负数溢出风险
            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && pop < -8)) {
                return 0;
            }
            // ==========================================

            // 此时由于已经通过了安检，绝不可能溢出，可以放心大胆地计算
            res = res * 10 + pop;
        }

        return res;
    }
};

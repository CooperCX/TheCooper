/*分段处理
1234 = NumberOf1Between1AndN_Solution(999) + NumberOf1Between1AndN_Solution(234) + 235
2234 = 2 * NumberOf1Between1AndN_Solution(999) + NumberOf1Between1AndN_Solution(234) + 235
*/

class countDigitOneSolution {
   public:
    int NumberOf1Between1AndN_Solution(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        if (n < 10) {
            return 1;
        }
        int high = n, pow = 1;
        while (high >= 10) {
            high /= 10;
            pow *= 10;
        }
        int last = n - high * pow;
        int cnt = (high == 1 ? last + 1 : pow);
        return cnt + NumberOf1Between1AndN_Solution(pow - 1) * high + NumberOf1Between1AndN_Solution(last);
    }

    int countDigitOne(int n) {
        if (n <= 0) {
            return 0;  // 遵循 RAII 与安全返回，小于等于0时直接防御性返回
        }
        int total_ones = 0;

        // 使用 long long 防止 digit * 10 时在最高位 (int 上限) 溢出
        long long digit = 1;

        int high = n / 10;
        int cur = n % 10;
        int low = 0;
        while (high != 0 || cur != 0) {
            if (cur == 0) {
                total_ones += high * digit;
            } else if (cur == 1) {
                total_ones += high * digit + low + 1;
            } else {
                total_ones += (high + 1) * digit;
            }

            // 更新指针和位，向左移一位
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return total_ones;
    }
};
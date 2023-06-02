/*分段处理
1234 = NumberOf1Between1AndN_Solution(999) + NumberOf1Between1AndN_Solution(234) + 235
2234 = 2 * NumberOf1Between1AndN_Solution(999) + NumberOf1Between1AndN_Solution(234) + 235
*/

class Solution {
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
};
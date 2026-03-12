#include <algorithm>
#include <cmath>
#include <vector>

class CutRopeSolution {
   public:
    // 解法一：数学推导与贪心（最优解 O(1) 或 O(logN) 时间复杂度）
    // 返回类型建议为 int。但在《剑指 Offer 14- II》中如果 N 获取非常大可能需要取模并使用 long
    // long，这里以基础版本为例。
    int cutRopeGreedy(int number) {
        // 如果绳子长度小于 2，按照题目约定无法剪出正整数段，或者按实际情况返回 0
        if (number < 2) {
            return 0;
        }
        // 当绳子长度为 2 时，只能剪成 1+1，乘积是 1
        if (number == 2) {
            return 1;
        }
        // 当绳子长度为 3 时，只能剪成 1+2，乘积是 2
        // 注意：只有在 number <= 3 且必须剪一刀的限制下，才会出现结果小于自身的情况。
        if (number == 3) {
            return 2;
        }

        // 当 number >= 4 时，我们就可以贪心地切分成 3 了 (因为 2*2=4，如果剩下的刚好是 4，切分成 2+2 或不切都是
        // 4，但如果是 5，切分成 3+2=6 > 5) 计算把绳子尽可能切成长度为 3 的段数
        int a = number / 3;
        // 计算切完后剩下的长度 (0, 1, 2)
        int b = number % 3;

        // 根据余数 b 的不同情况进行处理
        if (b == 0) {
            // 刚好能被 3 整除，全部都是 3，乘积最大
            return static_cast<int>(std::pow(3, a));
        } else if (b == 1) {
            // 如果余数是 1，把一个 3 拿出来，加上余数 1 变成 4，再均分为 2 * 2
            // 乘积就是 3^(a-1) * 4
            return static_cast<int>(std::pow(3, a - 1)) * 4;
        } else {  // b == 2
            // 如果余数是 2，直接把 2 乘上去，因为 2 > 1*1
            // 乘积就是 3^a * 2
            return static_cast<int>(std::pow(3, a)) * 2;
        }
    }

    // 解法二：动态规划 (时间复杂度 O(N^2)，作为补充和思维发散)
    int cutRopeDP(int number) {
        if (number < 2) return 0;
        if (number == 2) return 1;
        if (number == 3) return 2;

        // dp[i] 表示长度为 i 的绳子剪成 m 段后的最大乘积 (注意这里是不一定需要剪的内部子绳子长度)
        // 为了状态转移方便，这里的 dp[1], dp[2], dp[3] 存储的是它们自身的长度值，
        // 因为当外层绳子长度 >= 4 时，子绳子长度为 1, 2, 3 时不剪(保留自身长度)的收益更大。
        std::vector<int> dp(number + 1, 0);
        dp[1] = 1;
        dp[2] = 2;  // 注意这里是 2，因为作为 >=4 的子问题，长度为 2 时不切收益 > 切成 1*1
        dp[3] = 3;  // 注意这里是 3，因为作为 >=4 的子问题，长度为 3 时不切收益 > 切成 1*2

        // 从长度 4 开始递推
        for (int i = 4; i <= number; ++i) {
            int max_val = 0;
            // 因为剪切具有对称性，遍历到 i/2 即可
            for (int j = 1; j <= i / 2; ++j) {
                // 将长度为 i 的绳子分为两部分 j 和 i-j，利用已计算的最优解相乘
                max_val = std::max(max_val, dp[j] * dp[i - j]);
            }
            dp[i] = max_val;
        }

        return dp[number];
    }
};

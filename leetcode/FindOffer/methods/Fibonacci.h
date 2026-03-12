#include <vector>
class FibonacciSolution {
   public:
    // 解法一：滚动变量（时间 O(N), 空间 O(1)）
    int fib(int n) {
        if (n == 0) return 0;  // 边界条件：n=0 返回 0
        if (n == 1) return 1;  // 边界条件：n=1 返回 1

        // a 代表 F(n-2)，初始化为 F(0) = 0
        // b 代表 F(n-1)，初始化为 F(1) = 1
        int a = 0;
        int b = 1;
        int sum = 0;

        // 注意：多数情况下题目要求对结果取模（如剑指Offer原题经常要求模 1000000007）
        // 如果题目没要求，那用普通的加法即可；如果输入极大，记得把类型改成 long long 应对溢出，或加取模逻辑
        for (int i = 2; i <= n; ++i) {
            sum = a + b;  // 计算现有的 f(i)
            // sum = (a + b) % 1000000007; // 如果题目要求取模

            // 变量滚动：就像履带一样往前走
            a = b;    // 下一轮的 F(n-2) 是这轮的 F(n-1)
            b = sum;  // 下一轮的 F(n-1) 是这轮算出的 F(n)
        }
        return sum;  // 或者返回 b
    }

    int Fibonacci(int n) {
        // 如果 n 小于等于 1，直接返回 n (即 n=0 返回 0，n=1 返回 1)
        if (n <= 1) {
            return n;
        }
        // 1. 定义 dp 数组
        // dp[i] 表示第 i 项斐波那契数，因为要算到第 n 项，所以数组大小为 n + 1
        std::vector<int> dp(n + 1, 0);
        // 2. 初始化边界条件
        dp[0] = 0;
        dp[1] = 1;
        // 3. 状态转移，从前向后递推
        for (int i = 2; i <= n; ++i) {
            // 当前项的值等于前两项之和
            dp[i] = dp[i - 1] + dp[i - 2];

            // 注意：如果题目（如剑指 Offer）要求结果很大时取模，这里可以写成：
            // dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
        }
        // 4. 返回最终结果
        return dp[n];
    }
};

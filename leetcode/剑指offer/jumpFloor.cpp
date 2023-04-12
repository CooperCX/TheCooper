#include <vector>

class Solution {
public:
    /*
    所谓跳台阶，其实就是斐波那契数列
    一次可以跳上1级台阶，也可以跳上2级
    上到第n级，只能从第n-1级跳1级，或者从第n-2级跳2级
    */
    int jumpFloor(int number) {
        if (number == 1) {
            return 1;
        }else if (number == 2) {
            return 2;
        } else {
            return jumpFloor(number - 1) + jumpFloor(number - 2);
        }
    }
    /*
    所谓随意跳台阶，其实就是每次可以跳任意级的台阶
    跳到第n级，可以从第n-1级跳，也可以从第n-2级跳，也可以从第0级跳
    f(n) = f(n-1) + f(n-2) + ... + f(0)
    f(n-1) = f(n-2) + f(n-3) + ... + f(0)
    f(n) = f(n-1) * 2
    */
    int jumpFloorII(int number) {
        std::vector<int> dp(number + 1);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= number; i++) {
            dp[i] = 2 * dp[i - 1];
        }
        return dp[number];
    }
};
#include <vector>

class jumpFloorSolution {
   public:
    /*
    所谓跳台阶，其实就是斐波那契数列
    一次可以跳上1级台阶，也可以跳上2级
    上到第n级，只能从第n-1级跳1级，或者从第n-2级跳2级
    */
    int jumpFloor(int number) {
        if (number <= 2) return number;
        int prev2 = 1;  // 相当于 f(n-2)
        int prev1 = 2;  // 相当于 f(n-1)
        int current = 0;
        for (int i = 3; i <= number; ++i) {
            current = prev1 + prev2;  // 当前台阶的跳法 = 前两个状态之和
            // 游标集体向前滚动一步，为计算下一个阶梯做准备
            prev2 = prev1;
            prev1 = current;
        }
        return current;
    }
    /*
    所谓随意跳台阶，其实就是每次可以跳任意级的台阶
    跳到第n级，可以从第n-1级跳，也可以从第n-2级跳，也可以从第0级跳
    f(n) = f(n-1) + f(n-2) + ... + f(0)
    f(n-1) = f(n-2) + f(n-3) + ... + f(0)
    f(n) = f(n-1) * 2
    */
    int jumpFloorII(int number) {
        if (number <= 0) return 0;

        // 1 << (number - 1) 意思就是 1 乘以 2 的 (number - 1) 次方
        return 1 << (number - 1);
    }
};
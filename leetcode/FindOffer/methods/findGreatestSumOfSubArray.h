#include <vector>

class FindGreatestSumOfSubArraySolution {
   public:
    int FindGreatestSumOfSubArray(const std::vector<int>& array) {
        // 边界防护：如果数组为空，按照约定返回 0 或者抛出异常
        if (array.empty()) {
            return 0;
        }
        // max_sum 记录全局遇到过的最大子数组和，初始化为第一个元素
        int max_sum = array[0];
        // current_sum 记录以当前遍历到的元素结尾的子数组最大和，相当于优化后的 dp 变量
        int current_sum = array[0];
        // 从第二个元素开始遍历
        for (int i = 1; i < array.size(); ++i) {
            // 这是核心状态转移：
            // 如果前面的 current_sum 是正资产，则加上当前的元素。
            // 如果前面的 current_sum 是负资产，再加上只会拖累当前元素，不如当前元素自立门户。
            current_sum = std::max(current_sum + array[i], array[i]);

            // 每次更新当前连续最大和后，都去挑战一下全局最大和的记录
            max_sum = std::max(max_sum, current_sum);
        }
        return max_sum;
    }

    int FindGreatestSumOfSubArray(std::vector<int> array) {
        int n = array.size();
        int res = array[0];
        std::vector<int> dp(n, 0);
        dp[0] = array[0];
        for (int i = 1; i < n; i++) {
            dp[i] = std::max(dp[i - 1] + array[i], array[i]);
            res = std::max(dp[i], res);
        }
        return res;
    }
};
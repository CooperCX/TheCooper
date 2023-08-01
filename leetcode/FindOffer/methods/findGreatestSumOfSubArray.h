#include <vector>

class FindGreatestSumOfSubArraySolution {
public:
    int FindGreatestSumOfSubArray(std::vector<int> array) {
        int n = array.size();
        int res = array[0];
        for (int i = 1; i < n; i++) {
            array[i] = std::max(array[i], array[i] + array[i - 1]);
            res = std::max(array[i], res);
        }
        return res;
    }

    int FindGreatestSumOfSubArray(std::vector<int> array) {
        int n = array.size();
        int res = array[0];
        for (int i = 1; i < n; i++) {
            array[i] = std::max(array[i - 1], 0) +  array[i];
            res = std::max(array[i], res);
        }
        return res;
    }

    int FindGreatestSumOfSubArray(std::vector<int> array) {
        int n = array.size();
        int res = array[0];
        std::vector<int> dp(n ,0);
        dp[0] = array[0];
        for (int i = 1; i < n; i++) {
            dp[i] = std::max(dp[i - 1] + array[i], array[i]);
            res = std::max(dp[i], res);
        }
        return res;
    }
};
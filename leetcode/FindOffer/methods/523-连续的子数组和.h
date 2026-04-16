#include <unordered_map>
#include <vector>

// 如果两个前缀和 $Sum_i$ 和 $Sum_j$ 对 $k$ 取模的结果相同，那么它们之间的子数组和 $(Sum_j - Sum_i)$ 必定能被 $k$ 整除
inline bool checkSubarraySum(std::vector<int>& nums, int k) {
    if (nums.size() < 2 || k == 0) return false;

    std::unordered_map<int, int> remainer_map;
    remainer_map[0] = -1;

    int cur_sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        cur_sum += nums[i];

        int remainer = cur_sum % k;
        if (remainer_map.count(remainer)) {
            if (i - remainer_map[remainer] >= 2) return true;
        } else {
            remainer_map[remainer] = i;
        }
    }

    return false;
}
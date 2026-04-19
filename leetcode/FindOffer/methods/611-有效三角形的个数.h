#include <algorithm>
#include <vector>

// 排序 + 双指针：O(n^2)
inline int triangleNumber(std::vector<int>& nums) {
    int n = nums.size();
    if (n < 3) return 0;

    // 1. 先排序
    std::sort(nums.begin(), nums.end());

    int count = 0;
    // 2. 固定最长边 c
    for (int i = n - 1; i >= 2; --i) {
        int l = 0;
        int r = i - 1;

        // 3. 双指针寻找 a + b > c
        while (l < r) {
            if (nums[l] + nums[r] > nums[i]) {
                // 当满足条件时，l 到 r-1 之间的数作为第一个边也都满足条件
                count += (r - l);
                r--;
            } else {
                l++;
            }
        }
    }

    return count;
}

#include <algorithm>
#include <climits>
#include <vector>

/**
 * 4. 寻找两个正序数组的中位数
 * 解法：二分查找 (划分数组法)
 * 时间复杂度：O(log(min(m, n)))
 * 空间复杂度：O(1)
 */
inline double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    // 1. 确保在较短的数组上进行二分查找，优化效率
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }

    int m = nums1.size();
    int n = nums2.size();

    // 在 [0, m] 之间寻找 nums1 的划分点 i
    int left = 0, right = m;
    while (left <= right) {
        int i = (left + right) / 2;
        // 根据 i 自动确定 nums2 的划分点 j
        int j = (m + n + 1) / 2 - i;

        // 边界处理：处理划分点在边缘的情况
        int nums1LeftMax = (i == 0) ? INT_MIN : nums1[i - 1];
        int nums1RightMin = (i == m) ? INT_MAX : nums1[i];
        int nums2LeftMax = (j == 0) ? INT_MIN : nums2[j - 1];
        int nums2RightMin = (j == n) ? INT_MAX : nums2[j];

        // 判断划分是否正确
        if (nums1LeftMax <= nums2RightMin && nums2LeftMax <= nums1RightMin) {
            // 找到正确划分点
            if ((m + n) % 2 == 1) {
                // 总数为奇数，返回左半部分最大值
                return std::max(nums1LeftMax, nums2LeftMax);
            } else {
                // 总数为偶数，返回左侧最大和右侧最小的均值
                return (std::max(nums1LeftMax, nums2LeftMax) + std::min(nums1RightMin, nums2RightMin)) / 2.0;
            }
        } else if (nums1LeftMax > nums2RightMin) {
            // nums1 的左侧部分太大了，减小 i
            right = i - 1;
        } else {
            // nums1 的左侧部分太小了，增大 i
            left = i + 1;
        }
    }

    return 0.0;
}

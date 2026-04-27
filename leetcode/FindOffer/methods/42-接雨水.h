#include <algorithm>
#include <vector>

/**
 * 42. 接雨水
 * 解法：双指针 (O(n) 时间, O(1) 空间)
 * 原理：利用左右最大值中的较小者作为瓶颈来计算水量
 */
inline int trap(std::vector<int>& height) {
    if (height.empty()) return 0;

    int res = 0;
    int left = 0, right = height.size() - 1;
    int max_left = 0, max_right = 0;

    while (left < right) {
        // 核心逻辑：哪边的高度小，哪边就是当前位置的“瓶颈”
        if (height[left] < height[right]) {
            if (height[left] >= max_left) {
                // 更新左侧最大值
                max_left = height[left];
            } else {
                // 当前高度小于左侧最大值，可以接水
                res += max_left - height[left];
            }
            left++;
        } else {
            if (height[right] >= max_right) {
                // 更新右侧最大值
                max_right = height[right];
            } else {
                // 当前高度小于右侧最大值，可以接水
                res += max_right - height[right];
            }
            right--;
        }
    }

    return res;
}
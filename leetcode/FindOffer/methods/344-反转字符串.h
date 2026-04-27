#include <algorithm>
#include <vector>

/**
 * 344. 反转字符串
 * 解法：双指针 (O(n) 时间, O(1) 空间)
 */
inline void reverseString(std::vector<char>& s) {
    if (s.empty()) return;

    int left = 0;
    int right = s.size() - 1;

    while (left < right) {
        // 交换左右指针指向的字符
        std::swap(s[left], s[right]);

        // 移动指针
        left++;
        right--;
    }
}

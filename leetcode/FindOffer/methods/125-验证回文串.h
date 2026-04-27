#include <cctype>
#include <string>

/**
 * 125. 验证回文串
 * 解法：双指针 (O(n) 时间, O(1) 空间)
 */
inline bool isPalindrome(std::string s) {
    if (s.empty()) return true;

    int left = 0, right = s.length() - 1;

    while (left < right) {
        // 1. 从左向右寻找第一个有效的字母或数字
        while (left < right && !std::isalnum(s[left])) {
            left++;
        }
        // 2. 从右向左寻找第一个有效的字母或数字
        while (left < right && !std::isalnum(s[right])) {
            right--;
        }

        // 3. 比较（统一转为小写）
        if (std::tolower(s[left]) != std::tolower(s[right])) {
            return false;
        }

        left++;
        right--;
    }

    return true;
}

#pragma once

#include <string>
#include <string_view>
#include <algorithm>

namespace find_offer {

class Solution {
public:
    // 寻找最长回文子串
    // 使用 std::string_view 避免不必要的字符串拷贝
    std::string longestPalindrome(std::string_view s) {
        if (s.empty()) {
            return "";
        }

        int start = 0;
        int max_len = 0;

        // 内部 lambda 表达式，用于执行中心扩展
        // 返回以 left 和 right 为中心的回文串长度
        auto expand_around_center = [&](int left, int right) -> int {
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                left--;
                right++;
            }
            // 循环结束时，left 和 right 已经不满足回文条件，或者越界
            // 此时回文串的实际长度为 (right - 1) - (left + 1) + 1 = right - left - 1
            return right - left - 1;
        };

        for (int i = 0; i < s.length(); ++i) {
            // 奇数长度的回文串，中心为一个字符
            int len1 = expand_around_center(i, i);
            // 偶数长度的回文串，中心为两个字符中间的间隙
            int len2 = expand_around_center(i, i + 1);
            
            // 取两者的最大值
            int len = std::max(len1, len2);
            
            // 如果发现了更长的回文子串，更新起始位置和最大长度
            if (len > max_len) {
                max_len = len;
                // 计算起始位置：
                // 无论是奇数还是偶数长度，起始位置都可以用这个统一的公式计算
                start = i - (len - 1) / 2;
            }
        }

        // 返回最长回文子串，构造 std::string
        return std::string(s.substr(start, max_len));
    }
};

} // namespace find_offer

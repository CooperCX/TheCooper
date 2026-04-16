#include <string>
#include <vector>

class MinCoverSubStringSolution {
   public:
    std::string MoveWindow(const std::string& S, const std::string& T) {
        if (S.empty() || T.empty() || S.length() < T.length()) return "";

        // 1. need 数组记录 T 中各个字符到底需要多少个
        // 2. window 数组记录当前滑动窗口中各个字符有多少个
        int need[128] = {0};
        int window[128] = {0};

        int need_types = 0;  // 记录 T 中到底有几种不同的字符
        for (char c : T) {
            if (need[c] == 0) need_types++;
            need[c]++;
        }

        int left = 0, right = 0;  // 左右指针
        int valid_count = 0;      // 记录窗口中已经满足要求的字符种类数

        // 记录最小覆盖子串的起始索引及长度
        int start = 0, min_len = 2147483647;  // 用一个很大的数代替 INT_MAX

        while (right < S.length()) {  // 开始不断向右扩散窗口
            char c = S[right];
            right++;  // right 右移，窗口吃入新字符

            // 如果这个字符正好是我们需要的，我们就把它记录到 window 中
            if (need[c] > 0) {
                window[c]++;
                // 一旦窗口里这个字符的数量达标了，有效记录数就 + 1
                if (window[c] == need[c]) {
                    valid_count++;
                }
            }

            // 只要有效记录数 == 我们需要的总种类数，说明此时窗口已经覆盖了 T！
            // 【准备开始压缩左边界求最优解】
            while (valid_count == need_types) {
                // 如果这个窗口的长度比历史记录更短，赶紧更新记录
                if (right - left < min_len) {
                    start = left;
                    min_len = right - left;
                }

                // d 是我们将要吐出去的字符
                char d = S[left];
                left++;  // left 右移，窗口吐出旧字符

                // 如果吐出去的字符原本是我们需要的
                if (need[d] > 0) {
                    // 当吐出去以后，正好不满足数量要求了，那么有效记录数就必须 - 1
                    if (window[d] == need[d]) {
                        valid_count--;
                    }
                    // 扣除窗口里对这个字符的计数
                    window[d]--;
                }
            }
        }  // 结束外层 right 循环的扩张

        // 如果 min_len 依然是初始的那个大得离谱的值，说明全场跑完都没找到符合的
        return min_len == 2147483647 ? "" : S.substr(start, min_len);
    }
};

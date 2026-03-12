#include <string>
#include <vector>
class FirstNotRepeatingCharSolution {
   public:
    // 最优解法：基于数组的哈希统计与 const 引用传参
    int FirstNotRepeatingChar(const std::string& str) {
        if (str.empty()) {
            return -1;
        }
        // ASCII 字符集最多 256 个字符。
        // 使用定长数组代替 std::unordered_map，避免动态内存分配和哈希运算开销。
        // {} 表示初始化所有元素为 0。
        int char_counts[256] = {0};

        // 第一遍：统计每个字符出现的频率
        for (char ch : str) {
            // char 隐式转换为对应的 ASCII 整数，作为数组下标
            // 注意：若 char 默认带符号(_signed_)，当出现中文字符等扩展 ASCII 会变成负数导致数组越界
            // 本题通常是通用可见字符，若考虑更广泛的安全防御可加 unsigned 转换: char_counts[(unsigned char)ch]
            char_counts[static_cast<unsigned char>(ch)]++;
        }
        // 第二遍：按原字符串顺序寻找第一个计数为 1 的字符
        int n = str.length();
        for (int i = 0; i < n; ++i) {
            if (char_counts[static_cast<unsigned char>(str[i])] == 1) {
                return i;
            }
        }
        return -1;  // 没找到则返回 -1
    }
};
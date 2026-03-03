#include <string>
#include <vector>

class Solution {
   public:
    std::string solve(std::string IP) {
        if (IP.empty()) return "Neither";

        // 如果包含 '.', 则可能是 IPv4；如果包含 ':', 可能是 IPv6
        if (IP.find('.') != std::string::npos) {
            return isIPv4(IP) ? "IPv4" : "Neither";
        } else if (IP.find(':') != std::string::npos) {
            return isIPv6(IP) ? "IPv6" : "Neither";
        }

        return "Neither";
    }

   private:
    bool isIPv4(const std::string& IP) {
        int dots = 0;
        int i = 0, n = IP.length();

        while (i < n) {
            // 解析出 '.' 之间的一段字符
            int j = i;
            while (j < n && IP[j] != '.') {
                // 如果发现除了数字以外的其他字符，直接判定非法
                if (!isdigit(IP[j])) return false;
                j++;
            }

            // 如果两个 '.' 挨在一起 (长度为0) 或者 长度大于 3 (最多到255)，非法
            if (j == i || j - i > 3) return false;

            // 提取这一段字符串的内容计算数值
            // 这里因为我们上面已经限制了长度最多为 3，所以在手动算术转换时绝对不会发生内存越界溢出
            int num = 0;
            for (int k = i; k < j; ++k) {
                // 检查前导零：如果长度大于1，且第一位是 '0'，直接非法
                if (k == i && IP[k] == '0' && j - i > 1) return false;
                num = num * 10 + (IP[k] - '0');
            }

            // 计算出的数值必须在 0 - 255 之间
            if (num > 255) return false;

            // 跳过这一段，指针移到下一个片段的开头
            i = j + 1;

            // 如果遇到点，记录点号数量；
            // 【特殊边角】：如果是合法的四段，应该只有 3 个点。最后一个 j < n 触发说明它是点
            if (j < n) dots++;
        }

        // 必须存在且仅存在 3 个点，并且最后一位不能是点 (".")，比如 "1.1.1.1."
        return dots == 3 && IP.back() != '.';
    }
    bool isIPv6(const std::string& IP) {
        int colons = 0;
        int i = 0, n = IP.length();

        while (i < n) {
            int j = i;
            while (j < n && IP[j] != ':') {
                // IPv6 允许包含十六进制大小写字母及数字
                char c = IP[j];
                bool isHex = isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
                if (!isHex) return false;
                j++;
            }

            // IPv6 每段的长度必须在 [1, 4] 之间，且允许有前导0
            if (j == i || j - i > 4) return false;

            i = j + 1;

            if (j < n) colons++;
        }

        // 必须存在且仅存在 7 个冒号，并且最后一位不能是冒号
        return colons == 7 && IP.back() != ':';
    }
};
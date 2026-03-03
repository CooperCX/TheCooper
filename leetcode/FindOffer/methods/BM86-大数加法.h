#include <algorithm>
#include <string>

class Solution {
   public:
    std::string solve(std::string s, std::string t) {
        std::string result = "";

        // 1. 设置双指针，从两个字符串的末尾（个位）开始
        int i = s.length() - 1;
        int j = t.length() - 1;

        // 进位标识
        int carry = 0;
        // 2. 将三个条件合并在同一个 while 循环里，结构极端清晰：
        // 只要 s 没遍历完、或者 t 没遍历完、或者最后还有进位，循环就继续
        while (i >= 0 || j >= 0 || carry != 0) {
            // 提取当前位的值。如果指针越界了(即某个字符串已经加完了)，则这一位当 0 处理
            int x = i >= 0 ? s[i] - '0' : 0;
            int y = j >= 0 ? t[j] - '0' : 0;

            // 计算当前位的值和进位
            int sum = x + y + carry;

            // % 10 取出个位数拼接到结果里，/ 10 留作下一次进位
            result.push_back(sum % 10 + '0');  // 注意：push_back 追加在末尾
            carry = sum / 10;                  // 例如 15 / 10 = 1

            // 指针前移
            i--;
            j--;
        }
        // 3. 因为我们是追加在尾部，即个位在前面。所以最后一定要反转整个字符串
        std::reverse(result.begin(), result.end());

        return result;
    }
};
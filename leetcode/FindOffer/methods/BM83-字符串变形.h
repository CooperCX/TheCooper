#include <stack>
#include <string>

class StringTransSolution {
   public:
    std::string trans(std::string s, int n) {
        if (n == 0) return s;
        // 1. 第一步：遍历字符串，完成大小写字母的互相转换
        for (int i = 0; i < n; ++i) {
            if (s[i] >= 'a' && s[i] <= 'z') {
                s[i] -= 32;  // 小写转大写，或者写 s[i] = toupper(s[i]);
            } else if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] += 32;  // 大写转小写，或者写 s[i] = tolower(s[i]);
            }
        }
        // 2. 第二步：将整个句子整体翻转
        // 例如："hELLO  wORLD" => "DLROw  OLLEh"
        std::reverse(s.begin(), s.end());
        // 3. 第三步：再把每个颠倒的单词内部重新翻转一次，使其恢复正常的拼写顺序
        int start = 0;
        for (int i = 0; i <= n; ++i) {
            // [极其关键的判断条件]：遇到空格，或者到达了字符串的结尾(i == n)
            // 必须把 i == n 写在前面防越界短路，保证最后一个单词也能被处理
            if (i == n || s[i] == ' ') {
                // std::reverse 传的是左闭右开区间 [begin, end)
                std::reverse(s.begin() + start, s.begin() + i);

                // 更换下一个单词的起点（跳过当前的空格）
                start = i + 1;
            }
        }
        return s;
    }

    // leetcode 151
    std::string reverseWords(std::string s) {
        // 第一阶段：原地移除多余的空格（快慢指针法）
        int slow = 0;  // 慢指针：指向最终真实需要保留的字符位置
        for (int fast = 0; fast < s.length(); ++fast) {
            // 如果遇到不是空格的字符，就说明是个单词的字母，需要收集
            if (s[fast] != ' ') {
                // 如果慢指针不为0，说明前面已经收集过单词了，
                // 在新收集的这个单词之前，必须手动补上一个空格
                if (slow != 0) {
                    s[slow++] = ' ';
                }

                // 把这个单词的所有连续字母都挪到慢指针的位置
                while (fast < s.length() && s[fast] != ' ') {
                    s[slow++] = s[fast++];
                }
                // 注意：上面 while 循环结束时，fast 会停在一个空格上（或者越界）。
                // 外层的 for 循环还要执行 ++fast，恰好跳过了这个空格。
            }
        }

        // 缩容：把慢指针之后全都是垃圾字符的尾巴给砍掉
        s.resize(slow);
        // 第二阶段：将整个被清理干净的句子整体反转
        // 例： "the sky is blue" -> "eulb si yks eht"
        std::reverse(s.begin(), s.end());
        // 第三阶段：把每个颠倒的单词内部重新翻转一次
        int start = 0;
        for (int i = 0; i <= s.length(); ++i) {
            // 因为前后多余的空格已经全删了，中间也只有一个空格，
            // 所以直接用 i == s.length() 或者遇到 ' ' 来切分单词
            if (i == s.length() || s[i] == ' ') {
                std::reverse(s.begin() + start, s.begin() + i);
                start = i + 1;  // 下一个单词的起点
            }
        }
        return s;
    }
};
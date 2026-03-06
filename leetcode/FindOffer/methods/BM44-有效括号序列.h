/*
    有效的括号序列
    核心思想：利用栈的 LIFO (后进先出) 特性处理“最近匹配”问题
*/
#include <stack>
#include <string>
#include <unordered_map>
class BracketValidSolution {
   public:
    // 解法：哈希表映射 + 单栈匹配
    // 时间复杂度：O(N) (只需完整遍历一遍字符串)
    // 空间复杂度：O(N) (最坏情况下全是左括号，栈需存储所有字符 + 固定常数级哈希表开销)
    bool isValid(std::string s) {
        int n = s.size();

        // =============== 【防御与先决判定】 ===============
        // 剪枝绝杀：括号必须成双成对！总数是奇数必定不合法，直接干掉 O(1)
        if (n % 2 != 0) return false;
        if (n == 0) return true;
        // =============== 【核心字典表】 ===============
        // 定义“右半边”到“左半边”的映射。
        // 这极大地避免了代码中出现丑陋的 if-else if-else 嵌套
        std::unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        // 用于存放尚未匹配过的“左半边”括号
        std::stack<char> stack;
        // =============== 【流式审查机】 ===============
        for (const char& ch : s) {
            // 情况 1：遇到了【右半边括号】(在字典中找到了 key)
            if (pairs.count(ch)) {
                // 致命错误 1：栈里根本没有左半边等它 (也就是右边多出来了)
                // 致命错误 2：栈顶的那个左半边，跟我这个右边的品种不匹配！
                if (stack.empty() || stack.top() != pairs[ch]) {
                    return false;
                }
                // 成功消消乐：栈顶元素与当前右括号完美牵手，从栈中幸福消亡
                stack.pop();
            }
            // 情况 2：遇到了【左半边括号】
            else {
                // 无条件推入栈中，成为等待右边来解救的“单身狗”
                stack.push(ch);
            }
        }
        // =============== 【终场结算】 ===============
        // 如果循环走完了，栈也彻底清空了，说明没有任何人落单，返回 true。
        // 如果栈里还有东西 (比如 "((()"), 说明左边带队的人多出来了，返回 false。
        return stack.empty();
    }
};
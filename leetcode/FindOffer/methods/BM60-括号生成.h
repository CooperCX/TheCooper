#include <string>
#include <vector>

// - 什么是合法的括号对？
// - int flag => 0; 左括号加+1，右括号-1，遍历后=0；

class generateParenthesisSolution {
   public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> results;
        if (n <= 0) return results;
        // 全局（或者传递引用）维护一个状态树路径，避免按值传递字符串
        std::string current_path = "";

        backtrack(n, 0, 0, current_path, results);

        return results;
    }

   private:
    // 注意 current_path 是引用传递 (std::string&)
    void backtrack(int n, int left_count, int right_count, std::string& current_path,
                   std::vector<std::string>& results) {
        // 递归终止条件：当左括号和右括号都用够了 n 个，得到一个合法结果
        // （实际上这里只需要判断 current_path.length() == n * 2 也行）
        if (left_count == n && right_count == n) {
            results.push_back(current_path);
            return;
        }
        // 1. 尝试放入左括号 (Make choice -> Backtrack -> Undo choice)
        // 条件：左括号的数量还没有耗尽
        if (left_count < n) {
            current_path.push_back('(');  // 原位追加，无新内存开辟
            backtrack(n, left_count + 1, right_count, current_path, results);
            current_path.pop_back();  // 回溯现场，恢复状态
        }
        // 2. 尝试放入右括号 (Make choice -> Backtrack -> Undo choice)
        // 关键剪枝条件：当前已经使用的右括号数量必须严格少于左括号数量
        if (right_count < left_count) {
            current_path.push_back(')');
            backtrack(n, left_count, right_count + 1, current_path, results);
            current_path.pop_back();  // 回溯现场
        }
    }
};
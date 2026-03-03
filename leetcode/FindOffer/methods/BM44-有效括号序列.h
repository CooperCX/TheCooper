#include <stack>
#include <string>
#include <unordered_map>

class BracketValidSolution {
   public:
    bool isValid(std::string s) {
        int n = s.size();
        if (n % 2) return false;
        if (n == 0) return true;

        std::unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};

        std::stack<char> stack;

        for (const char& ch : s) {
            if (pairs.count(ch)) {
                if (stack.empty() || stack.top() != pairs[ch]) return false;
                stack.pop();
            } else {
                stack.push(ch);
            }
        }

        return stack.empty();
    }
};
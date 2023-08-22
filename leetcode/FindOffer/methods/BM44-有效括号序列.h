#include <unordered_map>
#include <stack>
#include <string>

class BracketValidSolution {
public:

    std::unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
    bool isValid(std::string s) {
        int n = s.length();
        if (n == 0 || n & 1) {
            return false;
        }
        std::stack<char> S;
        if (pairs.end() != pairs.find(s[0])) {
            return false;
        } else {
            S.push(s[0]);
        }
        for (int i = 1; i < n; i++) {
            if (pairs.end() != pairs.find(s[i])) {
                if (pairs[s[i]] != S.top()) {
                    return false;
                } else {
                    S.pop();
                }
            } else {
                S.push(s[i]);
            }
        }
        return S.empty();
    }
};
#include <vector>
#include <string>

// - 什么是合法的括号对？
// - int flag => 0; 左括号加+1，右括号-1，遍历后=0；

class generateParenthesisSolution {
public:

    std::vector<std::string> generateParenthesis(int n) {
        std::string temp;
        std::vector<std::string> results;
        generateCore(n, 0, 0, temp, results);
        return results;
    }

private:

    void generateCore(const int& n, int left, int right,
                      std::string temp, std::vector<std::string>& res)
    {
        if (left == n && right == n) {
            res.push_back(temp);
            return;
        }
        if (left < n) {
            generateCore(n, left + 1, right, temp + "(", res);
        }
        if (right < n && right < left) {
            generateCore(n, left, right + 1, temp + ")", res);
        }
    }
};
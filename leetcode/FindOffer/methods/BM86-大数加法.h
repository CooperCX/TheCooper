#include <string>
#include <algorithm>

class Solution {
public:

    std::string solve(std::string s, std::string t) {
        int n = s.length();
        int m = t.length();
        if (n < m) {
            std::swap(s, t);
        }
        int carry = 0;
        for (int i = s.length() - 1; i >= 0; i--) {
            int temp = s[i] - '0' + carry;
            int j = i - s.length() + t.length();
            if (j >= 0) {
                temp += t[j] - '0';
            }
            carry = temp / 10;
            temp %= 10;
            s[i] = temp + '0';
        }
        if (carry == 1) {
            s = "1" + s;
        }
        return s;
    }
};
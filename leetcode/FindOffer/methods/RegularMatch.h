#include <string>

class RegularMatchSolution {
public:
    bool match(std::string str, std::string pattern) {
        int len1 = str.length(), len2 = pattern.length();
        if (len1 == 0 && len2 == 0) {
            return true;
        }
        if (len1 != 0 && len2 == 0) {
            return false;
        }
        if (pattern[1] != '*') {
            if (str[0] == pattern[0] || (pattern[0] == '.' && str[0])) {
                return match(str.substr(1, len1 - 1), pattern.substr(1, len2 - 1));
            } else {
                return false;
            }
        } else {
            if (str[0] == pattern[0] || (pattern[0] == '.' && str[0])) {
                return match(str, pattern.substr(2, len2 - 2)) || match(str.substr(1, len1 - 1), pattern);
            } else {
                return match(str, pattern.substr(2, len2 - 2));
            }
        }
    }
};
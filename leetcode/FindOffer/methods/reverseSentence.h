#include <string>

class ReverseSentenceSolution {
public:
    std::string ReverseSentence(std::string str) {
        int n = str.length();
        std::string temp = "", result = "";
        for (int i = 0; i < n; i++) {
            if (str[i] == ' ') {
                result = " " + temp + result;
                temp = "";
            } else {
                temp = temp + str[i];
            }
        }
        if (!temp.empty()) {
            result = temp + result;
        }
        return result;
    }
};
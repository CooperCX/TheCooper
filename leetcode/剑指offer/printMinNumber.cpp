#include <vector>
#include <string>

class Solution {
public:
    std::string PrintMinNumber(std::vector<int> numbers) {
        std::vector<std::string> temp;
        for (int number : numbers) {
            temp.push_back(std::to_string(number));
        }
        std::sort(temp.begin(), temp.end(), [](std::string a, std::string b) {
            return a + b < b + a;
        });
        std::string result;
        for (auto t : temp) {
            result += t;
        }
        return result;
    }
};
/*顺子牌成立的条件：排序后，除了0都不相等，且max - min < 5*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int IsContinuous(std::vector<int> numbers) {
        int joker = 0;
        std::sort(numbers.begin(), numbers.end());
        for (int number : numbers) {
            if (number == 0) {
                joker++;
            }
        }
        for (int i = joker; i < 4; i++) {
            if (numbers[i] == numbers[i + 1]) {
                return false;
            }
        }
        return numbers[4] - numbers[joker] < 5;
    }
};
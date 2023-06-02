#include <vector>

/*摩尔投票法*/
class Solution {
public:
    int MoreThanHalfNum(std::vector<int> numbers) {
        int n = numbers.size();
        int cnt = 0, num = 0;
        for (int number : numbers) {
            if (cnt == 0) {
                num = number;
                cnt = 1;
            } else {
                number == num ? cnt++ : cnt--;
            }
        }
        cnt = std::count(numbers.begin(), numbers.end(), num);
        return cnt > n / 2 ? num : 0;
    }
};
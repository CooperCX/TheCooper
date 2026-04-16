#include <string>
class findNthDigitSolution {
public:
    int findNthDigit(int n) {
        // write code here
        int digit = 1;
        long long sum = 9;
        long long start = 1;
        while ( n > sum) {
            n -= sum;
            start *= 10;
            digit++;
            sum = 9 * start * digit;
        }
        int num = (n - 1) / digit + start;
        int index = (n  - 1) % digit;
        return std::to_string(num)[index] - '0';

    }
};
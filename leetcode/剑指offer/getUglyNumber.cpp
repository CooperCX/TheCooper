/*丑数：2^x * 3^y * 5^z*/

#include <vector>

class Solution {
public:
    int GetUglyNumber(int index) {
        if (index <= 6) {
            return index;
        }
        int x = 0, y = 0, z = 0;
        std::vector<int> results(index, 0);
        results[0] = 1;
        for (int i = 1; i < index; i++) {
            int number = std::min(std::min(results[x] * 2, results[y] * 3), results[z] * 5);
            if (number == results[x] * 2) {
                x++;
            }
            if (number == results[y] * 3) {
                y++;
            }
            if (number == results[z] * 5) {
                z++;
            }
            results[i] = number;
        }
        return results[index - 1];
    }
};
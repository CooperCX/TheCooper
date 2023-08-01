#include <vector>

class FindNumbersWithSumSolution {
public:
    std::vector<int> FindNumbersWithSum(std::vector<int> array,int sum) {
        std::vector<int> result;
        int n = array.size();
        if (n < 2 || sum < array[0]) {
            return result;
        }
        int start = 0, end = n - 1;
        while (start < end) {
            int total = array[start] + array[end];
            if (total == sum) {
                result.push_back(array[start]);
                result.push_back(array[end]);
                return result;
            } else if (total > sum) {
                end--;
            } else {
                start++;
            }
        }
        return result;
    }
};
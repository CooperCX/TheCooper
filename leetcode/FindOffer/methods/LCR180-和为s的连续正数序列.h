#include <vector>
class FindContinuousSequenceSolution {
   public:
    // 滑动窗口法
    std::vector<std::vector<int>> FindContinuousSequence(int sum) {
        std::vector<std::vector<int>> results;
        int start = 1, end = 2;
        while (start < end) {
            int totalSum = (start + end) * (end - start + 1) / 2;
            if (totalSum == sum) {
                std::vector<int> result;
                for (int i = start; i <= end; i++) {
                    result.push_back(i);
                }
                results.push_back(result);
                start++;
            } else if (totalSum > sum) {
                start++;
            } else {
                end++;
            }
        }
        return results;
    }
};
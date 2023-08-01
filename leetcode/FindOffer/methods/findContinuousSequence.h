#include <vector>
class FindContinuousSequenceSolution {
public:
    // 穷举法
    std::vector<std::vector<int>> FindContinuousSequence(int sum) {
        std::vector<std::vector<int>> results;
        if (sum < 3) {
            return results;
        }
        int k = 1;
        while (k <= sum) {
            std::vector<int> result;
            int S = 0;
            for (int i = k; i < sum; i++) {
                result.push_back(i);
                S += i;
                if (S < sum) {
                    continue;
                } else if (S > sum) {
                    result.clear();
                    break;
                } else {
                    results.push_back(result);
                    result.clear();
                }
            }
            k++;
        }
        return results;
    }

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
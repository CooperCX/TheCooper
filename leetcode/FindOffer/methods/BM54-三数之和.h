#include <vector>

class threeSumSolution {
public:

    std::vector<std::vector<int>> threeSum(std::vector<int>& num) {
        std::vector<std::vector<int>> results;
        int n = num.size();
        std::sort(num.begin(), num.end());
        if(n < 3) {
            return results;
        }

        for (int i = 0; i < n - 2; i++) {
            if ( i != 0 && num[i] == num[i - 1]) {
                continue;
            }
            int temp = -num[i];
            int start = i + 1, end = n - 1;
            while (start < end) {
                if (num[start] + num[end] == temp) {
                    results.push_back({num[i], num[start], num[end]});
                    while (start < end && num[start + 1] == num[start]) {
                        start++;
                    }
                    while (start < end && num[end - 1] == num[end]) {
                        end--;
                    }
                    start++;
                    end--;
                } else if (num[start] + num[end] > temp) {
                    end--;
                } else {
                    start++;
                }
            }
        }

        return results;
    }
};
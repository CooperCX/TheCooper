#include <vector>
#include <algorithm>

class Solution {
public:
    // 二分法
    int GetNumberOfK(std::vector<int> data, int k) {
        int n = data.size();
        if (n < 1) {
            return 0;
        }
        int start = 0, end = n - 1;
        if (data[start] > k || data[end] < k) {
            return 0;
        }
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (data[mid] > k) {
                end = mid - 1;
            } else if (data[mid] < k) {
                start = mid + 1;
            } else {
                int count = 1;
                int index = mid - 1;
                while (index >= 0 && data[index] == k) {
                    count++;
                    index--;
                }
                index = mid + 1;
                while (index <= n - 1 && data[index] == k) {
                    count++;
                    index++;
                }
                return count;
            }
        }
        return 0;
    }

    // STL方法
    int GetNumberOfK(std::vector<int> data, int k) {
        auto pos = std::equal_range(data.begin(), data.end(), k);
        return pos.second - pos.first;
    }
};
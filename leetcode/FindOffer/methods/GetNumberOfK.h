#include <vector>
#include <algorithm>

class GetNumberOfKSolution {
public:
    // 二分法
    int GetNumberOfK(std::vector<int> data, int k) {
        return biSearch(data, k + 0.5) - biSearch(data, k - 0.5);
    }
private:
    int biSearch(std::vector<int> data, float k) {
        int n = data.size();
        int start = 0, end = n - 1;
        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (data[mid] > k) {
                end = mid - 1;
            } else if (data[mid] < k) {
                start = mid + 1;
            }
        }
        return start;
    }

public:
    // STL方法
    int GetNumberOfK(std::vector<int> data, int k) {
        auto pos = std::equal_range(data.begin(), data.end(), k);
        return pos.second - pos.first;
    }
};
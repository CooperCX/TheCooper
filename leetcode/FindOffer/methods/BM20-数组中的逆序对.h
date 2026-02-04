#include <ctime>
#include <vector>

class InversePairsSolution {
   public:
    int reversePairs(std::vector<int>& data) {
        if (data.empty()) return 0;
        int n = data.size();
        std::vector<int> temp(n, 0);
        return static_cast<int>(mergeSortAndCount(data, temp, 0, n - 1));
    }

   private:
    long long mergeSortAndCount(std::vector<int>& data, std::vector<int>& temp, int start, int end) {
        if (start >= end) return 0;

        int mid = start + (end - start) / 2;

        long long count =
            (mergeSortAndCount(data, temp, start, mid) + mergeSortAndCount(data, temp, mid + 1, end)) % 1000000007;

        int i = start, j = mid + 1, k = start;
        while (i <= mid && j <= end) {
            if (data[i] <= data[j]) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
                count += mid - i + 1;
            }
        }

        while (i <= mid) temp[k++] = data[i++];
        while (j <= end) temp[k++] = data[j++];

        for (int p = start; p <= end; p++) {
            data[p] = temp[p];
        }

        return count;
    }
};
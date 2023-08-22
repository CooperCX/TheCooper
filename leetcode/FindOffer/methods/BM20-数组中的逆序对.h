#include <vector>

class findInversePairsinArrayInversePairsSolution {
public:
    int findInversePairsinArrayInversePairs(std::vector<int> data) {
        int n = data.size();
        std::vector<int> temp(n, 0);
        return InversePairsCore(data, temp, 0, n - 1);
    }
private:
    int InversePairsCore(std::vector<int>& data, std::vector<int>& temp, int begin, int end) {
        if (begin >= end) {
            return 0;
        }
        int mid = begin + (end - begin) / 2;
        int lbegin = begin, lend = mid, rbegin = mid + 1, rend = end;
        int left = InversePairsCore(data, temp, lbegin, lend);
        int right = InversePairsCore(data, temp, rbegin, rend);
        int res = 0;
        for (int i = begin; i <= end; i++) {
            temp[i] = data[i];
        }
        int index = begin;
        while (lbegin <= lend && rbegin <= rend) {
            if (temp[lbegin] < temp[rbegin]) {
                data[index++] = temp[lbegin++];
            } else {
                data[index++] = temp[rbegin++];
                res += (lend - lbegin + 1);
                res %= 1000000007;
            }
        }
        while (lbegin <= lend) {
            data[index++] = temp[lbegin++];
        }
        while (rbegin <= rend) {
            data[index++] = temp[rbegin++];
        }
        return (left + right + res) % 1000000007;
    }
};
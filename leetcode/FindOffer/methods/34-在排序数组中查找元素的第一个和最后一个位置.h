#include <vector>
class GetNumberOfKSolution {
   public:
    std::vector<int> GetNumberOfK(const std::vector<int>& data, int k) {
        if (data.empty()) return {-1, -1};

        int left_bound = getLeftBound(data, k);
        // 如果连左边界都没找到（或者找到的值不是 k），说明数组里根本没这个数
        if (left_bound == -1) return {-1, -1};

        int right_bound = getRightBound(data, k);

        // 结束位置 - 开始位置 + 1 就是总个数
        return {left_bound, right_bound};
    }

   private:
    // 寻找目标值 k 出现的第一个位置（左边界）
    int getLeftBound(const std::vector<int>& data, int k) {
        int left = 0, right = data.size() - 1;
        int first_pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (data[mid] == k) {
                // 找到了 k，但它未必是第一个！
                // 我们把它记录下来，然后强行把右边界移到 mid-1，继续在左侧逼近
                first_pos = mid;
                right = mid - 1;
            } else if (data[mid] > k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return first_pos;
    }
    // 寻找目标值 k 出现的最后一个位置（右边界）
    int getRightBound(const std::vector<int>& data, int k) {
        int left = 0, right = data.size() - 1;
        int last_pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (data[mid] == k) {
                // 找到了 k，但它未必是最后一个！
                // 把它记录下来，然后强行把左边界移到 mid+1，继续在右侧逼近
                last_pos = mid;
                left = mid + 1;
            } else if (data[mid] > k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return last_pos;
    }
};
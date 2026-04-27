#include <vector>

/**
 * 977. 有序数组的平方
 * 解法：双指针 (O(n) 时间, O(1) 空间)
 */
inline std::vector<int> sortedSquares(std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n);

    int left = 0;
    int right = n - 1;
    int pos = n - 1;  // 从右向左填充，先存最大的

    while (left <= right) {
        int left_square = nums[left] * nums[left];
        int right_square = nums[right] * nums[right];

        if (left_square > right_square) {
            res[pos--] = left_square;
            left++;
        } else {
            res[pos--] = right_square;
            right--;
        }
    }

    return res;
}

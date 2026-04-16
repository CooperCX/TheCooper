#include <vector>

inline int maxArea(std::vector<int>& height) {
    if (height.empty()) return 0;
    int left = 0, right = height.size() - 1;

    int max_square = 0;
    while (left < right) {
        int square = (right - left) * std::min(height[left], height[right]);
        max_square = std::max(max_square, square);
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }

    return max_square;
}
#include <vector>

inline void moveZeroes(std::vector<int>& nums) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); ++fast) {
        if (nums[fast]) std::swap(nums[slow++], nums[fast]);
    }
}
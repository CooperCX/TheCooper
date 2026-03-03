#include <vector>

class threeSumSolution {
   public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        int n = nums.size();
        if (n < 3) return results;

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            int temp = -nums[i];

            int left = i + 1, right = n - 1;
            while (left < right) {
                if (nums[left] + nums[right] == temp) {
                    results.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left + 1] == nums[left]) left++;
                    while (left < right && nums[right - 1] == nums[right]) right--;
                    left++;
                    right--;
                } else if (nums[left] + nums[right] < temp) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return results;
    }
};
#include <unordered_map>
#include <vector>

class minNumberDisappearedSolution {
public:

    int minNumberDisappeared(std::vector<int>& nums) {
        std::unordered_map<int, int> hash;
        for (int num : nums) {
            hash[num]++;
        }
        int res = 1;
        while (hash.find(res) != hash.end()) {
            res++;
        }
        return res;
    }

    int minNumberDisappeared(std::vector<int>& nums) {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int minZ = 1;
        if (nums[n - 1] <= 0 || nums[0] > 1) {
            return minZ;
        }
        for (int i = 1; i <= nums[n - 1] + 1; i++) {
            if (std::find(nums.begin(), nums.end(), i) == nums.end()) {
                minZ = i;
                break;
            }
        }
        return minZ;
    }
};
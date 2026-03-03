#include <unordered_map>
#include <vector>

class minNumberDisappearedSolution {
   public:
    int minNumberDisappeared1(std::vector<int>& nums) {
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

    // 对于一个长度为 n 的数组，它里面缺失的第一个正数一定落在区间 [1, n + 1] 之间
    int minNumberDisappeared2(std::vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] < n && nums[nums[i] - 1] != nums[i]) {
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) return i + 1;
        }

        return n + 1;
    }
};
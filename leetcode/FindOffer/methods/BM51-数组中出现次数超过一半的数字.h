#include <vector>

/*摩尔投票法*/
class MoreThanHalfNumSolution {
   public:
    int MoreThanHalfNum(std::vector<int> nums) {
        int n = nums.size();
        if (0 == n) return 0;

        int cnt = 0, candidate = 0;
        for (int i = 0; i < n; i++) {
            if (0 == cnt) {
                candidate = nums[i];
            }
            cnt += candidate == nums[i] ? 1 : -1;
        }

        cnt = std::count(nums.begin(), nums.end(), candidate);
        return cnt > n / 2 ? candidate : 0;
    }
};
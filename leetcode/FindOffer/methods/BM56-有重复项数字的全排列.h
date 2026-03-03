#include <algorithm>
#include <unordered_map>
#include <vector>

class recursionUniqueSolution {
   public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        std::vector<int> path;
        std::vector<bool> used(nums.size(), false);

        std::sort(nums.begin(), nums.end());

        backtrack(nums, path, used, results);

        return results;
    }

   private:
    void backtrack(const std::vector<int>& nums, std::vector<int>& path, std::vector<bool>& used,
                   std::vector<std::vector<int>>& results) {
        if (path.size() == nums.size()) {
            results.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i - 1] == nums[i] && !used[i - 1]) continue;

            path.push_back(nums[i]);
            used[i] = true;

            backtrack(nums, path, used, results);

            used[i] = false;
            path.pop_back();
        }
    }
};
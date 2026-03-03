#include <algorithm>
#include <unordered_map>
#include <vector>

class recursionSolution {
   public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        std::vector<int> temp;
        std::vector<bool> used(nums.size(), false);

        backtrack(nums, used, temp, results);

        return results;
    }

   private:
    void backtrack(const std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& temp,
                   std::vector<std::vector<int>>& results) {
        if (temp.size() == nums.size()) {
            results.push_back(temp);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;

            temp.push_back(nums[i]);
            used[i] = true;

            backtrack(nums, used, temp, results);

            used[i] = false;
            temp.pop_back();
        }
    }
};
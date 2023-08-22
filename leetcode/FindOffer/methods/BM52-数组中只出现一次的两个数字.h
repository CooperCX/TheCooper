#include <unordered_map>
#include <vector>

class FindNumsAppearOnceSolution {
public:
    // hash
    std::vector<int> FindNumsAppearOnce(std::vector<int>& nums) {
        std::vector<int> results;
        int n = nums.size();
        std::unordered_map<int, int> hash;
        for (int i = 0; i < n; i++) {
            hash[nums[i]]++;
        }
        for (auto pair : hash) {
            if (pair.second == 1) {
                results.push_back(pair.first);
            }
        }
        std::sort(results.begin(), results.end());
        return results;
    }
    // 异或
    std::vector<int> FindNumsAppearOnce(std::vector<int>& nums) {
        std::vector<int> results(2, 0);
        int n = nums.size();
        int temp = 0;
        for (auto num : nums) {
            temp ^= num;
        }
        int k = 1;
        while ((temp & k) == 0) {
            k <<= 1;
        }
        for (int i = 0; i < n; i++) {
            if ((k & nums[i]) == 0) {
                results[0] ^= nums[i];
            } else {
                results[1] ^= nums[i];
            }
        }
        std::sort(results.begin(), results.end());
        return results;
    }
};
#include <unordered_map>
#include <vector>

inline int subarraySum(std::vector<int>& nums, int k) {
    if (nums.empty()) return 0;

    std::unordered_map<int, int> hash;
    hash[0] = 1;

    int count = 0;
    int prefixSum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        prefixSum += nums[i];
        int diff = prefixSum - k;
        if (hash.count(diff)) {
            count += hash[diff];
        }
        hash[prefixSum]++;
    }

    return count;
}
#include <unordered_map>
#include <vector>

class twoSumSolution {
public:

    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int n = numbers.size();
        std::vector<int> res;
        std::unordered_map<int, int> hash;
        for (int i = 0; i < n; i++) {
            if (hash.find(target - numbers[i]) == hash.end()) {
                hash[numbers[i]] = i;
            } else {
                res.push_back(hash[target - numbers[i]] + 1);
                res.push_back(i + 1);
                break;
            }
        }


        return res;
    }
};
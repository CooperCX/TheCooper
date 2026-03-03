#include <unordered_map>
#include <vector>

class FindNumsAppearOnceSolution {
   public:
    // hash
    std::vector<int> FindNumsAppearOnce(std::vector<int>& nums) {
        std::vector<int> results;
        std::unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            hash[nums[i]]++;
        }
        for (auto pair : hash) {
            if (pair.second == 1) results.push_back(pair.first);
        }

        return results;
    }
    // 异或
    std::vector<int> singleNumber(std::vector<int>& nums) {
        int xor_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            xor_sum ^= nums[i];
        }

        // int k = 1;
        // while ((xor_sum & k) == 0) {
        //     k <<= 1;
        // }
        // 提取一个整型数字二进制表示中最右侧（最低位）的 1，可以只用一行位运算解决：k = temp & (-temp)
        unsigned int k = static_cast<unsigned int>(xor_sum) & -(static_cast<unsigned int>(xor_sum));

        int res1 = 0, res2 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] & k) {
                res1 ^= nums[i];
            } else {
                res2 ^= nums[i];
            }
        }

        return {res1, res2};
    }
};
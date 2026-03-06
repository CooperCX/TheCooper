/*
    两数之和 (Two Sum)
    力扣万恶之源，哈希表空间换时间的绝对经典。
    大厂标准解法：单遍哈希 (One-pass Hash Table)
*/

#include <unordered_map>
#include <vector>

class twoSumSolution {
   public:
    // 解法：边存边查的单遍哈希字典法
    // 时间复杂度：O(N) (只需遍历一次数组，每次哈希查找的平均时间是 O(1))
    // 空间复杂度：O(N) (最坏情况下，找不到配对时，整个数组的数据都要存进哈希表)
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // 哈希字典：专门用来记录“曾经来过的人”
        // Key   = 数组中的具体数值 (nums[i])
        // Value = 这个数值所在的下标位置 (i)
        std::unordered_map<int, int> hash;

        for (int i = 0; i < nums.size(); i++) {
            // 当前数字 nums[i] 的“天命之子”应该是： target - nums[i]
            // 我们去历史记录本(哈希表)里翻一翻，看看这个人之前出现过没有？
            auto it = hash.find(target - nums[i]);

            if (it != hash.end()) {
                // 如果找到了！说明它不仅存在，而且它当时的下标已经被我们记录在 it->second 里了
                // 把它的旧下标，和我们当前的新下标 i，打包返回！
                return {it->second, i};
            }

            // 如果没找到，说明不仅之前没人能跟我配对，也许站在我后面的人，他要找的正是【我】！
            // 所以我必须把 【我的值】 和 【我的下标 i】 登记在册，留给后人去 find。
            hash[nums[i]] = i;
        }

        // 题目往往保证有解，如果实在没解，返回空数组防御
        return {};
    }
};

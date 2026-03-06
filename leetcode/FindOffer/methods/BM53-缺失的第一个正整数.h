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
    int minNumberDisappeared(std::vector<int>& nums) {
        int n = nums.size();
        // 第一阶段：暴力归位 (原地哈希)
        // 目标：让数字 i 乖乖地呆在 nums[i-1] 这个下标坑位上。
        for (int i = 0; i < n; i++) {
            // 条件 1：这个数是个有效的正整数 (非负数非零)
            // 条件 2：这个数字没有大到离谱，它在 [1, n] 的范围内，我们数组里有坑能装下它！
            // 条件 3：它该呆的那个专属坑位 nums[nums[i]-1] 里，目前装的并不是它本尊 (防死循环)
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                // 把当前这个不守规矩的萝卜 nums[i] 扔回它属于的 nums[nums[i]-1] 坑里
                // 顺便把那个坑里不属于那里的数字揪过来，供下一轮 while 继续帮它找生母
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }
        // 第二阶段：查缺补漏
        // 现在理论上所有的合法数字都已经呆在自己的对应下标里了
        for (int i = 0; i < n; i++) {
            // 下标 i 这个坑位，理论上必须要供奉着数字 i+1
            // 一旦发现货不对板，说明数字 i+1 压根就没有出现在这一片大地上！它就是失踪的最小正数！
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        // 终极情况：如果这片大地全员拉满，完美贴合 1, 2, 3, ..., N
        // 那缺失的第一个正数只能是被外包到天涯海角的 N + 1 了
        return n + 1;
    }
};
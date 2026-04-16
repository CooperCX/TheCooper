#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> subsets1(vector<int>& nums) {
        int n = nums.size();
        int total_subsets = 1 << n;  // 相当于 2 的 n 次方

        vector<vector<int>> results;

        // 遍历这 2^N 种组合 (0 到 2^N - 1)
        for (int mask = 0; mask < total_subsets; ++mask) {
            vector<int> current_subset;

            // 针对当前的 mask（比如 011），挨个检查它的每一位 (一共检查 n 位)
            for (int i = 0; i < n; ++i) {
                // 如果掩码的第 i 位是 1，说明我们要抓取这个数字
                if ((mask & (1 << i)) != 0) {
                    current_subset.push_back(nums[i]);
                }
            }

            // 这个子集凑齐了，加入总成果里
            results.push_back(current_subset);
        }

        return results;
    }

    vector<vector<int>> subsets2(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> current_path;  // 这里的 path 就是那个“篮子”

        // 从第 0 个商品开始做决定
        dfs(nums, 0, current_path, results);

        return results;
    }

   private:
    void dfs(const vector<int>& nums, int index, vector<int>& path, vector<vector<int>>& results) {
        // 【出口】如果流水线走到了尽头 (所有商品都看过了)
        if (index == nums.size()) {
            // 立刻把篮子里当前的结果打包，送上货车 (加入到最终结果集中)
            results.push_back(path);
            return;
        }
        // ============ 决定 1：我偏【不选】当前的数字 ============
        // 既然不选，篮子(path)里什么都不加，直接去考察下一个商品 (index + 1)
        dfs(nums, index + 1, path, results);
        // ============ 决定 2：我决定【选】当前的数字 ============
        // 把它放进篮子里
        path.push_back(nums[index]);
        // 放完之后，满怀期待地去考察下一个商品 (index + 1)
        dfs(nums, index + 1, path, results);
        // 【核心操作：回溯、恢复现场】
        // 当刚刚那条“我选了它”的路线彻底跑完，准备退回上一层时，
        // 必须要把吃进去的这个商品吐出来！这样才能清空篮子，让父节点或者兄弟节点重新做决定。
        path.pop_back();
    }
};

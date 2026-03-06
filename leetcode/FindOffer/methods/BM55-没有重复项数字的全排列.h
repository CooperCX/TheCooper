/*
    没有重复项数字的全排列 (Permutations)
    核心思想：DFS + 回溯算法 (Backtracking)
    回溯模板口诀：判断终结条件 -> 遍历当前层候选 -> 做选择 -> 递归下一层 -> 撤销选择
*/
#include <vector>
class recursionSolution {
   public:
    // 解法：DFS 全排列套路
    // 时间复杂度：O(N * N!) (全排列的总数是 N!，每次保存排列需要 O(N) 的拷贝开销)
    // 空间复杂度：O(N) (递归深度为 N，used 和 temp 数组占用 O(N) 空间)
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> results;
        std::vector<int> temp;  // 当前正在试探的这一条路径 (手里的包)

        // 核心性能点：用一个 bool 数组记录 nums 中哪个位置的数字已经被选过了。
        // 这极大地避免了每次去 temp 里查重的 O(N) 开销，属于空间换时间的典范。
        std::vector<bool> used(nums.size(), false);
        backtrack(nums, used, temp, results);
        return results;
    }

   private:
    void backtrack(const std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& temp,
                   std::vector<std::vector<int>>& results) {
        // ================= 1. 递归终止条件 =================
        // 如果手里这条路上捡到的数字个数，已经等于数组总长度，
        // 说明我们成功凑齐了一套全排列，直接入库保存！
        if (temp.size() == nums.size()) {
            results.push_back(temp);
            return;
        }
        // ================= 2. 遍历本层所有可能的候选 =================
        for (int i = 0; i < nums.size(); i++) {
            // 【过滤无效选择】：如果这个位置的数字已经被当前路径的主力军用了，跳过
            if (used[i] == true) continue;
            // ================= 3. 回溯三大步 =================
            // 第一步：【做选择】(去拿这个数字)
            temp.push_back(nums[i]);
            used[i] = true;  // 打上标记：这哥们正在被我征用！
            // 第二步：【深搜盲钻】(带着他去探索未来的路)
            backtrack(nums, used, temp, results);
            // 第三步：【撤销选择】(我探索完了从深渊回来了，或者撞到南墙退回来了)
            // 我现在要把现场洗得干干净净，仿佛我从未点过他，
            // 这样我才能毫无心理负担地在下个循环里去点别人！
            used[i] = false;  // 解除标记：你可以回营地待命了。
            temp.pop_back();  // 从这条路径里除名。
        }
    }
};
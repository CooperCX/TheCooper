/*
    滑动窗口的最大值
    核心思想：单调双端队列 (Monotonic Deque)
    金句法则：“如果一个新人比你年轻，还比你强，那你就永远没有出头之日了”
*/
#include <deque>
#include <vector>
class maxInWindowsSolution {
   public:
    // 解法：借助双端队列实现 O(N) 滑窗极值搜索
    // 队列里存的是【下标】，因为我们需要靠下标来判断一个人是不是“过期”（滑出窗口）了
    // 队列里的数值对应的一定是严格单调递减的。
    std::vector<int> maxInWindows(const std::vector<int>& nums, unsigned int size) {
        std::vector<int> results;
        int n = nums.size();
        // 【防御】如果数组为空，或者窗口比整个数组还长，或者窗口大小为 0 (C++防溢出)
        if (n == 0 || size > n || size == 0) return results;
        // 双端队列，方便头删（淘汰老将）和尾删（淘汰弱鸡）
        std::deque<int> q;
        for (int i = 0; i < n; i++) {
            // ================= 1. 右侧淘汰弱鸡 (维护单调性) =================
            // 只要当前新来的数字，大于或等于队列尾部的数字
            // 那么队列尾部那些“又老（下标小）又弱（值小）”的人就可以永远滚蛋了，
            // 留着他们没有任何意义，因为只要新来的在一天，他们就不可能当老大。
            while (!q.empty() && nums[i] > nums[q.back()]) {
                q.pop_back();
            }
            // 新来的人不管多弱，因为他最年轻，总有熬出头的那一天（当前面的老将都过期之后）
            q.push_back(i);
            // ================= 2. 左侧淘汰老将 (维护窗口大小) =================
            // q.front() 毫无疑问是当前队伍的最强者
            // 但如果他的下标已经被当前的滑窗左边界（i - size）甩在后面了，说明他已经过期了
            // （注意：这里是 i - q.front() >= size，比如当前 i=3，size=3，那么 q.front() 最多只能是 1）
            if (i - q.front() >= size) {
                q.pop_front();
            }
            // ================= 3. 记录当前窗口老大 =================
            // 我们的滑窗是在下标到达 size - 1 时才初步成型的，从这一步开始才发结果
            if (i >= size - 1) {
                // 队伍的最前端，永远是当前这批人里的神！
                results.push_back(nums[q.front()]);
            }
        }
        return results;
    }
};
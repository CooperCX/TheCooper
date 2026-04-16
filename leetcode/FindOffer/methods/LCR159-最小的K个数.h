/*
    最小的 K 个数 (Top K 问题)
    核心思想：大根堆 (Priority Queue) 容量截断法
    经典场景：应对海量数据（如十亿个数）或无尽数据流，内存仅需 O(K) 级开销
*/

#include <functional>
#include <queue>
#include <vector>

class GetLeastNumbersSolution {
   public:
    // 解法：容量为 k 的大根堆
    // 时间复杂度：O(N log K)，N是总数字量。每次调整大小为 k 的堆的时间是 logK。
    // 空间复杂度：O(K)，内存中只需要常驻维护这 K 个数字。
    std::vector<int> GetLeastNumbers_Solution(const std::vector<int> numbers, int k) {
        std::vector<int> results;
        int n = numbers.size();

        // =============== 【防御与极限剪枝】 ===============
        if (n == 0 || k <= 0) return results;  // 没数字，或者 k 不合理，直接退
        if (k >= n) {
            // 如果要找的 K 比整体数字还多，那还挑什么？直接全员打包端走！
            // 这里利用了 C++ vector 的深拷贝，直接返回原数组
            results = numbers;
            return results;
        }

        // =============== 【核心武器：大根堆】 ===============
        // C++ 标准库的 priority_queue 默认就是最大值在上面的大根堆 (`std::less<int>`)
        std::priority_queue<int> max_heap;

        for (int i = 0; i < n; i++) {
            // 阶段 1：堆还没装满 K 个人，不论是谁一律先放进去占坑
            if (max_heap.size() < k) {
                max_heap.push(numbers[i]);
            }
            // 阶段 2：坑位已满 K 个，开启残酷的末位淘汰制
            else {
                // max_heap.top() 站着的是当前这 K 个人里“最大”的家伙（也就是最容易被淘汰出局的人）
                // 只有当外面的新人比目前暂定的最大老将【还小】时，新人材有资格进来
                if (numbers[i] < max_heap.top()) {
                    max_heap.pop();             // 把原来的老大末位淘汰
                    max_heap.push(numbers[i]);  // 纳入更有潜力更小的新人
                }
            }
        }

        // =============== 【结算成果】 ===============
        // 扫完整个数组后，大根堆里幸存下来的，就是全国最小的 K 个人
        while (!max_heap.empty()) {
            results.push_back(max_heap.top());
            max_heap.pop();
        }

        return results;
    }
};

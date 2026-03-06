/*
    数据流中的中位数
    核心思想：双堆法（对顶堆）
    数据分成降序的小值区（大根堆）和升序的大值区（小根堆）
*/

#include <queue>
#include <vector>

class MedianFinder {
   public:
    MedianFinder() {}

    // ==========================================
    // 流式添加入队
    // 时间复杂度：O(log N)
    // 空间复杂度：O(N) (两个堆加起来存所有的数字)
    // ==========================================
    void addNum(int num) {
        count++;  // 全局计数器

        // 核心法门：通过互相“过水”洗掉身份不明的数字，维持绝对的大小分隔。
        // 人为规定：如果总数是奇数，左边（大根堆）必须比右边（小根堆）多出一个人。

        if (count & 1) {
            // 当前这步走完应该是奇数，也就是说本次行动需要往【左边大根堆】里多塞一个人。
            // 盲套法：先把这个未知实力的数字塞到【右边小根堆】里去
            right_min_heap.push(num);
            // 右边小根堆经过内部消化，会把目前里面【最小】的一个人顶到最上面（.top()）
            // 我们直接把这个最底层的弱者抽调出来，塞到左边大根堆去！
            left_max_heap.push(right_min_heap.top());
            right_min_heap.pop();  // 收尾：将那个不幸被抽调走的人从右边踢出
        } else {
            // 当前这步走完应该是偶数，两边人数需要完全对等。
            // 盲套法：先把这人塞到【左边大根堆】
            left_max_heap.push(num);
            // 左边大根堆会把个头【最大】的内鬼顶到最上面
            // 我们把这个过于强大的内鬼抽调到右边去！
            right_min_heap.push(left_max_heap.top());
            left_max_heap.pop();
        }
    }

    // ==========================================
    // 查询中位数
    // 时间复杂度：极速 O(1)
    // ==========================================
    double findMedian() {
        // 如果是奇数，根据我们在 addNum 中的设定，左边必定刚好比右边多一个。
        // 所以整个王国的核心，就是左边大根堆堆顶的那个人。
        if (count & 1) return left_max_heap.top();

        // 如果是偶数，说明两边人数刚刚好打平，中位数必须要由两边的护法老大结合计算。
        return (left_max_heap.top() + right_min_heap.top()) / 2.0;
    }

   private:
    int count = 0;  // 全局元素总数

    // “左边池子”：大根堆 (Max Heap)。负责装全天下【较小】的那一半数字。
    // 池子顶部是这群较小数字里【最大】的一个，也就是左护法。
    std::priority_queue<int, std::vector<int>, std::less<int>> left_max_heap;

    // “右边池子”：小根堆 (Min Heap)。负责装全天下【较大】的那一半数字。
    // 池子顶部是这群较大数字里【最小】的一个，也就是右护法。
    std::priority_queue<int, std::vector<int>, std::greater<int>> right_min_heap;
};

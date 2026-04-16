#include <vector>
class InversePairsSolution {
   public:
    // 解法：基于归并排序求逆序对 (分治思想)
    // 时间复杂度 O(N log N)，空间复杂度 O(N) (需要 temp 数组)
    int reversePairs(std::vector<int>& data) {
        if (data.empty()) return 0;
        int n = data.size();

        // 【工程绝招】在最外层提前只开辟一次 O(N) 的临时内存池
        // 千万不要在递归内部 new/vector，那会导致 O(N log N) 的内存分配和剧烈的性能震荡！
        std::vector<int> temp(n, 0);

        return static_cast<int>(mergeSortAndCount(data, temp, 0, n - 1));
    }

   private:
    long long mergeSortAndCount(std::vector<int>& data, std::vector<int>& temp, int start, int end) {
        // 递归终止条件：区间内只有 1 个甚至 0 个元素，不可能有任何对子
        if (start >= end) return 0;
        int mid = start + (end - start) / 2;
        // 【分治】分别计算左半区、右半区内部的逆序对，并且把它们各自排好序
        long long count = mergeSortAndCount(data, temp, start, mid) + mergeSortAndCount(data, temp, mid + 1, end);

        // 力扣不要求取模，但剑指 offer/牛客通常要求结果对 1e9+7 取模
        count %= 1000000007;
        // 【合并】计算横跨左右两区的逆序对 (此时左右两区内部绝对升序！)
        int i = start;    // 左半区探索游标
        int j = mid + 1;  // 右半区探索游标
        int k = start;    // temp 辅助数组的写入游标
        while (i <= mid && j <= end) {
            // 如果左边 <= 右边，说明顺序是对的（或者相等构不成严格逆序），直接让左边入列
            if (data[i] <= data[j]) {
                temp[k++] = data[i++];
            } else {
                // 如果左边 > 右边，说明左边这个数字，比右边的游标数字大了！
                // 因为左半区别排过序，所以左边从 i 到 mid 的【所有数字】全都会比右边游标大！
                temp[k++] = data[j++];

                // 一次性加上这一批所有的逆序对
                count += (mid - i + 1);
                count %= 1000000007;  // 累加后安全取余
            }
        }
        // 把剩下的残兵败将收编进 temp (下面这两个 while 最多只会执行其中一个)
        while (i <= mid) temp[k++] = data[i++];
        while (j <= end) temp[k++] = data[j++];
        // 将这一轮 [start, end] 排好序的 temp 倒回真正的战场原数组中
        for (int p = start; p <= end; p++) {
            data[p] = temp[p];
        }
        return count;
    }
};
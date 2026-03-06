#include <vector>

class BiSearchSolution {
   public:
    // 解法：二分查找 (闭区间 [start, end] 模板)
    // 时间复杂度 O(log N)，空间 O(1)
    int search(std::vector<int>& nums, int target) {
        // 【防御性编程】空数组直接淘汰
        if (nums.empty()) return -1;
        // 【闭区间设定】我们要在 [0, n - 1] 这个闭区间里寻找 target
        int start = 0, end = nums.size() - 1;
        // 既然是闭区间，当 start == end 时，区间内仍然有一个合法元素需要被检验
        // 如果这里写成 <，就会在最后一步漏掉 start 等于 end 时的那个孤立节点
        while (start <= end) {
            // 【工程素养极其重要】防止 Integer Overflow 整数溢出的终极解法
            // 严禁写成 (start + end) / 2
            int mid = start + (end - start) / 2;

            // 下方这种写法可以利用右移运算获得极其微弱的速度提升 (但现代编译器会自动优化)
            // int mid = start + ((end - start) >> 1);
            if (nums[mid] < target) {
                // mid 已经检验过了，明确不要，所以新的左边界从 mid + 1 开始计算
                start = mid + 1;
            } else if (nums[mid] > target) {
                // mid 已经检验过了，明确不要，所以新的右边界从 mid - 1 开始计算
                end = mid - 1;
            } else {
                // 找到了唯一真相目标
                return mid;
            }
        }

        // 直到 start 跨越了 end (区间变成反义的空集)，依然没找到，返回 -1
        return -1;
    }
};
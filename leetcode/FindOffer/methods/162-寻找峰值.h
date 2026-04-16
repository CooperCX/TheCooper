#include <vector>
class findPeakElementSolution {
   public:
    // 解法：二分查找寻找局部极值 (左侧夹逼/右紧缩模板)
    // 时间复杂度 O(log N)，空间 O(1)
    int findPeakElement(std::vector<int>& nums) {
        // [前置防御] 如果想要更严谨，可以加上判空
        // if (nums.empty()) return -1;

        int n = nums.size();

        // 1. 初始化左右指针
        int start = 0, end = n - 1;
        // 2. 注意这里的退出条件：是不带等号的 <
        // 这意味着只要 start 和 end 没重合就继续挤压，一旦重合 (start == end) 循环终止。
        // 这也能保证循环内部，start 永远小于 end，所以 mid + 1 绝对不会越界！
        while (start < end) {
            // 安全的取中点防溢出
            int mid = start + (end - start) / 2;

            // 爬山理论：
            // 假设我们当前在半山腰 (mid)，看了一眼右前方的一步 (mid + 1)
            // 如果比当前高 (上坡路)
            if (nums[mid] < nums[mid + 1]) {
                // 峰顶一定在前面，所以我们勇敢地往前走一步，把悬崖绝后
                start = mid + 1;
            } else {
                // 右边比当前矮 (下坡路)，说明峰顶在左边，
                // 但是！我们当前站的地方 (mid) 自己可能就是那个顶峰！
                // 所以我们向左收缩时，必须把 mid 给保留在嫌疑人名单里
                end = mid;
            }
        }

        // 当 start 和 end 殊途同归相聚的那一刻，就是唯一的顶峰
        return start;
    }
};
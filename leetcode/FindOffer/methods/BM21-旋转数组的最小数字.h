#include <vector>
class minNumberInRotateArraySolution {
   public:
    // 解法：二分查找寻找旋转临界谷底 (右侧端点比较法)
    // 时间复杂度 平均 O(log N)，最坏退化情况 O(N) (全数组元素相等时)
    // 空间复杂度 O(1)

    // 【极大关键点】记得传 const&，否则每次递归或调用都要拷贝一整个数组！
    int minNumberInRotateArray(const std::vector<int>& rotateArray) {
        if (rotateArray.empty()) return 0;

        // 我们套用之前写过的 “挤压逼近区间模板 [start, end)”
        int start = 0, end = rotateArray.size() - 1;
        // 依然是不带等号的 <，只要 start 和 end 没撞在一起就继续夹逼
        while (start < end) {
            int mid = start + (end - start) / 2;

            // 绝杀法则：在旋转数组中作案，永远拿 mid 和 右端点 end 比较

            if (rotateArray[mid] > rotateArray[end]) {
                // mid 大于右端点，说明 mid 当前身处左半高地。
                // 真正的谷底一定在右边 (甚至 mid 本身绝对不可能是极小值)
                start = mid + 1;

            } else if (rotateArray[mid] < rotateArray[end]) {
                // mid 小于右端点，说明 mid 已经掉下悬崖来到了右半低谷。
                // 谷底可能在左边，也可能 mid 就是谷底本人！所以不能跨越它！
                end = mid;

            } else {
                // 极其恶心的重复元素出现了 (e.g., [1, 1, 1, 0, 1])
                // 我们无法判断谷底在左还是右，但我们确信：把最右边的这个端点删掉是稳赚不赔的，
                // 因为就算这个被删掉的数是极小值，mid 的位置还有一个一模一样的替补！
                end--;
            }
        }

        // 挤压到最后，start 所在之处，就是万丈深渊的最底端
        return rotateArray[start];
    }
};
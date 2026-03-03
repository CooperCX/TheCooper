#include <vector>
class Solution {
   public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        // 1. 设置三个指针，分别指向各自的末尾
        int p1 = m - 1;     // nums1 中实际数字的尾部
        int p2 = n - 1;     // nums2 中的数字尾部
        int p = m + n - 1;  // nums1 容器的绝对尾部（最终安放数据的位置）

        // 2. 从后往前遍历，进行"大树乘凉"：谁的值大，就把谁填在最后面
        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p] = nums1[p1];
                p1--;
            } else {
                nums1[p] = nums2[p2];
                p2--;
            }
            p--;  // 存放位指针不管谁放了，都要往前挪一格
        }

        // 3. 收尾工作（【极度关键】的处理点）：
        // 循环跳出时，有可能 p1 < 0（即 nums1 里的数提前被安放完了），但 nums2 里还有剩的。
        // 因为剩下的 nums2 数字一定是最小的，而且 nums1 最前面刚好空出了位置，直接平移覆盖过去即可。
        // 注意：如果是 p2 先走完了（< 0），那 nums1 剩下没动的数本身就在原位且是有序的，什么都不用管。
        while (p2 >= 0) {
            nums1[p] = nums2[p2];
            p2--;
            p--;
        }
    }
};
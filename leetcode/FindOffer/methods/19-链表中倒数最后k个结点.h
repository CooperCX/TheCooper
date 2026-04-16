#include "../include/struct_define.h"

class FindKthToTailSolution {
   public:
    // 经典解法：快慢双指针
    // 时间复杂度 O(N)，只遍历一遍链表；空间复杂度 O(1)
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        // 第一步：定义快慢指针，同一起跑线
        ListNode* fast = pListHead;
        ListNode* slow = pListHead;
        // 第二步：让 fast 也就是尺子的右边界，先向前走 k 步
        // 这样 fast 和 slow 之间就拉开了 k 的差距
        while (k > 0) {
            if (fast != nullptr) {
                fast = fast->next;
            } else {
                // 【鲁棒性】：如果跑着跑着发现没路了，说明链表总长度 < k，直接防御性返回 null
                return nullptr;
            }
            k--;
        }
        // 第三步：fast 和 slow 同步向后平移，直到 fast 触底
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        // 此时 fast 变成了 nullptr，意味着尺子右边悬空，
        // 那么 slow 这个尺子左边界刚好落在倒数第 k 个节点上。
        return slow;
    }
};

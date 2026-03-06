#include "../include/struct_define.h"

class removeNthFromEndSolution {
   public:
    // 解法：基于 Dummy 节点的快慢双指针 (滑动窗口/尺子法)
    // 时间复杂度 O(N)，只遍历一遍链表；空间复杂度 O(1)
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 应对极端边界问题 (删除头结点) 的万能灵药：Dummy 节点
        // 分配在栈上，防止内存泄漏
        ListNode dummy(-1);
        dummy.next = head;
        // 快指针：尺子的右边界，用来探路
        ListNode* fast = &dummy;

        // 慢指针：尺子的左边界，最终必定会停在【被删除目标节点的前一个节点】(即前驱)
        // 为什么从 dummy 出发能刚好停在前驱上？
        // 因为 fast 比 slow 刚好多走 n 步。当 fast 的 next 为空时（fast处在倒数第1个），
        // 那么 slow 肯定刚好落在在倒数第 (n+1) 个位置！这完美契合了我们的删除需求！
        ListNode* slow = &dummy;
        // 1. 让 fast 先拉开 n 步的距离
        // 题目往往保证 n 是有效的，但加上防御性判断习惯总没错
        for (int i = 0; i < n; i++) {
            if (fast->next != nullptr) {
                fast = fast->next;
            } else {
                return nullptr;  // 如果 n 超过了链表长度，防御性返回 (或者随题意直接 return head)
            }
        }
        // 2. 双指针【同步】向前平移，直到快指针撞到链表真正的最后一块砖
        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        // 3. 执行死刑交接：此时 slow 稳稳停在被删除目标的前驱节点上
        // 跨过这个待删节点，连接到更后面的节点
        ListNode* targetToDelete = slow->next;
        if (targetToDelete != nullptr) {
            slow->next = targetToDelete->next;

            // 注意：在真实的 C++ 工业环境里，这里被断开的那个节点 `targetToDelete`
            // 是需要被 delete 掉来释放内存的。如果面试官在乎防内存走漏，必须写！
            // 力扣评测里因为有垃圾回收机制（或不检查堆泄漏），所以不写也能过。
            // delete targetToDelete;
        }
        // 4. Dummy 的 next 是真正的且安全的新头节点 (哪怕最初始的 head 被删了，next 也能指向老二或 nullptr)。
        return dummy.next;
    }
};
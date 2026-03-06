#include "BM4-合并两个排序链表.h"

class sortInSingleListSolution {
   public:
    // 解法：自顶向下的归并排序 (分治法)
    // 时间复杂度 O(N log N)，空间复杂度 O(log N) (递归栈)
    ListNode* sortInList(ListNode* head) {
        // 1. 递归终止条件：当链表为空或只有一个节点时，天然有序
        if (!head || !head->next) return head;
        // 2. 寻找链表中点 (快慢指针法)
        ListNode* slow = head;
        ListNode* fast = head->next;  // 这样 slow 最终会稳稳停在左半部分的最后一个节点
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // 3. 断开链表，分成左右两半
        ListNode* midNode = slow->next;  // 记录好右半部分的开头
        slow->next = nullptr;            // 【极其关键】切断左半部分
        // 4. 对左右两半分别进行递归排序
        ListNode* leftSorted = sortInList(head);
        ListNode* rightSorted = sortInList(midNode);
        // 5. 将两个已经有序的链表合并 (直接复用我们前面神级写法的 BM4)
        return mergeListSolution::mergeList(leftSorted, rightSorted);
    }
};
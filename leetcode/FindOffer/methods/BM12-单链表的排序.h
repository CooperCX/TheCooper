#include "BM4-合并两个排序链表.h"

class sortInSingleListSolution {
   public:
    ListNode* sortInList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* prev = nullptr;
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        if (prev) prev->next = nullptr;

        return mergeListSolution::mergeList(sortInList(head), sortInList(slow));
    }
};
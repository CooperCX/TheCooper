#include "../include/struct_define.h"

class removeNthFromEndSolution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy = ListNode(-1);
        dummy.next = head;

        ListNode* pre = &dummy;
        ListNode* slow = head;
        ListNode* fast = head;

        while (n > 0) {
            if (fast) {
                fast = fast->next;
            } else {
                return nullptr;
            }
            n--;
        }
        while (fast) {
            pre = pre->next;
            slow = slow->next;
            fast = fast->next;
        }

        pre->next = slow->next;
        return dummy.next;
    }
};
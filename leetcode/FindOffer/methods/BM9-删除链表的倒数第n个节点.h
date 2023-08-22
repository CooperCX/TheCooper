#include "../include/struct_define.h"

class removeNthFromEndSolution {
public:

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* pre = dummy;
        ListNode* slow = head;
        ListNode* fast = head;
        while (n) {
            fast = fast->next;
            n--;
        }
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
            pre = pre->next;
        }
        pre->next = slow->next;

        return dummy->next;
    }

};
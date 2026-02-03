#include <vector>

#include "../include/struct_define.h"

class isPailSolution {
   public:
    bool isPail(ListNode* head) {
        // write code here
        if (!head || !head->next) return true;

        ListNode* slow = head;
        ListNode* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // ListNode* head2 = reverseListNode(slow);
        ListNode* head2 = nullptr;
        ListNode* cur = slow;
        while (cur) {
            ListNode* post = cur->next;
            cur->next = head2;
            head2 = cur;
            cur = post;
        }

        while (head2) {
            if (head->val != head2->val) return false;
            head = head->next;
            head2 = head2->next;
        }
        return true;
    }
};
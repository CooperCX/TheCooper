#include "../include/struct_define.h"

class deleteDuplicates2Solution {
   public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode dummy(-1);
        dummy.next = head;

        ListNode* pre = &dummy;

        while (pre->next && pre->next->next) {
            if (pre->next->val == pre->next->next->val) {
                int val = pre->next->val;
                while (pre->next && val == pre->next->val) {
                    ListNode* delete_node = pre->next;
                    pre->next = pre->next->next;
                    delete delete_node;
                }
            } else {
                pre = pre->next;
            }
        }

        return dummy.next;
    }
};
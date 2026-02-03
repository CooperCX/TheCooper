#include "../include/struct_define.h"

class deleteDuplicates1Solution {
   public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* cur = head;

        while (cur && cur->next) {
            if (cur->next->val == cur->val) {
                ListNode* delete_code = cur->next;
                cur->next = cur->next->next;
                delete delete_code;
            } else {
                cur = cur->next;
            }
        }

        return head;
    }
};
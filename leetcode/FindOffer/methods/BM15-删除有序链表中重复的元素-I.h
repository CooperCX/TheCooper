#include "../include/struct_define.h"

class deleteDuplicates1Solution {
  public:

    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto cur = dummy->next;

        while (cur->next != nullptr) {
            if (cur->val == cur->next->val) {
                int temp = cur->val;
                while (cur->next != nullptr && cur->next->val == temp) {
                    cur->next = cur->next->next;
                }
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};
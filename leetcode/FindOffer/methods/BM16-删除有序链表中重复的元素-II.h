#include "../include/struct_define.h"

class deleteDuplicates2Solution {
  public:

    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto pre = dummy;

        while (pre->next != nullptr && pre->next->next != nullptr) {
            if (pre->next->val == pre->next->next->val) {
                int temp = pre->next->val;
                while (pre->next != nullptr && pre->next->val == temp) {
                    pre->next = pre->next->next;
                }
            } else {
                pre = pre->next;
            }
        }
        return dummy->next;
    }
};
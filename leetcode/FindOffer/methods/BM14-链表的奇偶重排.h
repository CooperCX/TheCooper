#include "../include/struct_define.h"

class oddEvenListSolution {
   public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head || !head->next) return head;

        ListNode* odd = head;
        ListNode* even_head = head->next;
        ListNode* even = even_head;

        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }

        odd->next = even_head;

        return head;
    }
};
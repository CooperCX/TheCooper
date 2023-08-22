#include "../include/struct_define.h"

class reverseBetweenSolution {
public:

    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // write code here
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* cur = head;

        for (int i = 1; i < m; i++) {
            pre = pre->next;
            cur = cur->next;
        }

        for (int i = m; i < n; i++) {
            ListNode* post = cur->next;
            cur->next = post->next;
            post->next = pre->next;
            pre->next = post;
        }

        return dummy->next;
    }
};
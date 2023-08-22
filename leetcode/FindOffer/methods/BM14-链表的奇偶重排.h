#include "../include/struct_define.h"


class oddEvenListSolution {
public:

    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* odd = head;
        auto oddhead = odd;
        ListNode* even = head->next;
        auto evenhead = even;

        int index = 3;
        head = head->next->next;
        while (head != nullptr) {
            if (index & 1) {
                odd->next = head;
                odd = odd->next;
            } else {
                even->next = head;
                even = even->next;
            }
            head = head->next;
            index++;
        }

        even->next = nullptr;
        odd->next = evenhead;

        return oddhead;
    }
};
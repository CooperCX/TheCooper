#include "../include/struct_define.h"
#include "BM1-反转链表.h"

class addInListSolution {
public:

    ListNode* addInList(ListNode* head1, ListNode* head2) {
        if (head1 == nullptr) {
            return head2;
        }
        if (head2 == nullptr) {
            return head1;
        }
        head1 = reverseListSolution::reverseList(head1);
        head2 = reverseListSolution::reverseList(head2);

        auto res = new ListNode(-1);
        ListNode* head = res;
        int carry = 0;

        while (head1 != nullptr || head2 != nullptr || carry != 0) {
            int num1 = (head1 == nullptr) ? 0 : head1->val;
            int num2 = (head2 == nullptr) ? 0 : head2->val;

            int temp = num1 + num2 + carry;
            carry = temp / 10;
            temp %= 10;
            head->next = new ListNode(temp);
            head = head->next;

            if (head1 != nullptr) {
                head1 = head1->next;
            }
            if (head2 != nullptr) {
                head2 = head2->next;
            }
        }

        return reverseListSolution::reverseList(res->next);
    }
};
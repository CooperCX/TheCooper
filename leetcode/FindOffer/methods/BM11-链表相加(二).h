#include <cstddef>
#include <stack>

#include "BM1-反转链表.h"

class addInListSolution {
   public:
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        head1 = reverseListSolution::reverseList(head1);
        head2 = reverseListSolution::reverseList(head2);

        ListNode* resNode = nullptr;
        int carry = 0;

        while (head1 || head2 || carry) {
            int sum = carry + (head1 ? head1->val : 0) + (head2 ? head2->val : 0);
            carry = sum / 10;

            // 头插法
            ListNode* newNode = new ListNode(sum % 10);
            newNode->next = resNode;
            resNode = newNode;

            if (head1) head1 = head1->next;
            if (head2) head2 = head2->next;
        }

        return resNode;
    }

    // 借助栈，不修改原链表
    ListNode* addInListByStack(ListNode* head1, ListNode* head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        std::stack<int> stack1, stack2;

        ListNode* curr1 = head1;
        while (curr1) {
            stack1.push(curr1->val);
            curr1 = curr1->next;
        }

        ListNode* curr2 = head2;
        while (curr2) {
            stack2.push(curr2->val);
            curr2 = curr2->next;
        }

        ListNode* resNode = nullptr;
        int carry = 0;
        while (!stack1.empty() || !stack2.empty() || carry) {
            if (!stack1.empty()) {
                carry += stack1.top();
                stack1.pop();
            }

            if (!stack2.empty()) {
                carry += stack2.top();
                stack2.pop();
            }

            ListNode* newNode = new ListNode(carry % 10);
            newNode->next = resNode;
            resNode = newNode;

            carry = carry / 10;
        }

        return resNode;
    }
};
#include "../include/struct_define.h"
#include "BM4-合并两个排序链表.h"

class sortInSingleListSolution {
public:

    ListNode* sortInList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* left = head;
        ListNode* mid = head->next;
        ListNode* right = head->next->next;
        while (right != nullptr && right->next != nullptr) {
            left = left->next;
            mid = mid->next;
            right = right->next->next;
        }
        left->next = nullptr;
        return mergeListSolution::mergeList(sortInList(head), sortInList(mid));
    }
};
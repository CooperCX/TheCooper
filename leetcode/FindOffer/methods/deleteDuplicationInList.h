#include "../include/struct_define.h"

class deleteDuplicationSolution {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        if (pHead ==nullptr || pHead->next == nullptr) {
            return pHead;
        }
        ListNode newNode(0);
        newNode.next = pHead;

        ListNode* pre = &newNode;
        ListNode* cur = pHead;

        while (cur != nullptr) {
            if (cur->next != nullptr && cur->val == cur->next->val) {
                while (cur->next != nullptr && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                pre->next = cur->next;
                cur = cur->next;
            } else {
                pre = pre->next;
                cur = cur->next;
            }
        }
        return newNode.next;
    }
};
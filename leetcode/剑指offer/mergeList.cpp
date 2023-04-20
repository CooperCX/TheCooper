#include "struct_define.h"

/*思路类似mergeSort*/
ListNode* mergeList(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) {
        return l2;
    }
    if (l2 == nullptr) {
        return l1;
    }
    ListNode head(-1);
    ListNode* node = &head;
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            node->next = l1;
            l1 = l1->next;
            node = node->next;
        } else {
            node->next = l2;
            l2 = l2->next;
            node = node->next;
        }
    }
    if (l1) {
        node->next = l1;
    }
    if (l2) {
        node->next = l2;
    }
    return head.next;
}
#include "../include/struct_define.h"

class FindKthToTailSolution {
    // 快慢指针
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* slowNode = pListHead;
        while (k > 0) {
            if (pListHead) {
                pListHead = pListHead->next;
            } else {
                return nullptr;
            }
            k--;
        }
        while (pListHead) {
            slowNode = slowNode->next;
            pListHead = pListHead->next;
        }
        return slowNode;
    }
};

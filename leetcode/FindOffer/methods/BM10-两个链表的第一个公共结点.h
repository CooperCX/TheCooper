#include "../include/struct_define.h"

class FindFirstCommonNodeSolution {
public:
    ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
        if (pHead1 == nullptr || pHead2 == nullptr) {
            return nullptr;
        }
        ListNode* node1 = pHead1;
        ListNode* node2 = pHead2;

        while (node1 != node2) {
            if (node1 == nullptr) {
                node1 = pHead2;
            } else {
				node1 = node1->next;
			}

            if (node2 == nullptr) {
                node2 = pHead1;
            } else {
				node2 = node2->next;
			}
        }

        return node1;
    }
};
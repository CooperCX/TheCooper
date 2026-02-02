#include <queue>
#include <vector>

#include "BM4-合并两个排序链表.h"

class mergeKListsSolution {
   public:
    ListNode* mergeKListsRecursive(std::vector<ListNode*>& lists) {
        // write code here
        if (lists.empty()) return nullptr;

        int n = lists.size();

        return mergeKListsCore(lists, 0, n - 1);
    }

   private:
    ListNode* mergeKListsCore(std::vector<ListNode*>& lists, int start, int end) {
        if (start > end) {
            return nullptr;
        } else if (start == end) {
            return lists[start];
        } else {
            int mid = (end - start) / 2 + start;
            return mergeListSolution::mergeList(mergeKListsCore(lists, start, mid),
                                                mergeKListsCore(lists, mid + 1, end));
        }
    }

   public:
    ListNode* mergeKListsIterative(std::vector<ListNode*>& lists) {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        std::priority_queue<ListNode*, std::vector<ListNode*>, compareListNode> pq;

        for (ListNode* head : lists) {
            if (head) pq.push(head);
        }

        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            tail->next = node;
            tail = tail->next;
            if (node->next) pq.push(node->next);
        }
        return dummy.next;
    }
};
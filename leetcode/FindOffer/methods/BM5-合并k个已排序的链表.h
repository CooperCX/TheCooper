#include "../include/struct_define.h"
#include "BM4-合并两个排序链表.h"
#include <vector>

class mergeKListsSolution {
public:

    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // write code here
        int n = lists.size();

        return mergeKListsCore(lists, 0, n - 1);
    }

    friend class mergeListSolution;

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


};
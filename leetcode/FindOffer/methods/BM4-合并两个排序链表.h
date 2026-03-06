#include "../include/struct_define.h"

class mergeListSolution {
   public:
    // 解法一：经典迭代法 (时间 O(N+M), 空间 O(1))
    static ListNode* mergeList(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        ListNode dummy(-1);
        ListNode* node = &dummy;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                node->next = l1;
                l1 = l1->next;
            } else {
                node->next = l2;
                l2 = l2->next;
            }
            node = node->next;  // 尾指针前移
        }

        // 当其中一个链表为空时，直接将尾指针指向另一个没遍历完的链表
        node->next = (l1 != nullptr) ? l1 : l2;

        return dummy.next;
    }
    // 解法二：黑魔法递归法 (时间 O(N+M), 空间: 最差情况栈深 O(N+M))
    static ListNode* mergeListRecursive(ListNode* l1, ListNode* l2) {
        // 1. 递归终止条件(Base Case)：
        // 任何一个链表耗尽，直接把对方整条链表返回作为接盘侠
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        // 2. 哪边的头较小，哪边就充当合并后的“头”保留下来
        // 并且让这个头去牵手剩下的、由递归神仙算好的链表合并结果
        if (l1->val <= l2->val) {
            l1->next = mergeListRecursive(l1->next, l2);
            return l1;  // 这个小头目向上一层汇报自己是真正的头
        } else {
            l2->next = mergeListRecursive(l1, l2->next);
            return l2;
        }
    }
};
#include "../include/struct_define.h"

class FindFirstCommonNodeSolution {
   public:
    // 解法：双指针追击算法 (时间 O(m+n), 空间 O(1))
    ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
        // 【防御性编程】只要有任何一条链表是空的，绝不可能有交集
        if (pHead1 == nullptr || pHead2 == nullptr) return nullptr;
        ListNode* node1 = pHead1;
        ListNode* node2 = pHead2;
        // node1 != node2 是最精髓的判断
        // 第一种情况：有交点。两指针都会走过 a+b+c 的路程，然后在交点相遇 (node1 == node2)。
        // 第二种情况：无交点。两指针都会走完自己的路+对方的路 (a+b)，并同时指向 nullptr！
        // 因为 nullptr == nullptr，循环也会干净利落地退出。
        while (node1 != node2) {
            // node1 走完了自己的路，不要停，去接盘走 node2 的路
            if (node1 == nullptr) {
                node1 = pHead2;
            } else {
                node1 = node1->next;
            }
            // node2 做同样的事情去接 node1 的路
            if (node2 == nullptr) {
                node2 = pHead1;
            } else {
                node2 = node2->next;
            }

            // 下面的精简优雅写法（使用三目运算符），如果你想把代码压缩到极点：
            // node1 = (node1 != nullptr) ? node1->next : pHead2;
            // node2 = (node2 != nullptr) ? node2->next : pHead1;
        }
        // 此时 node1 无论是有效的公共节点，还是代表平行的 nullptr，都是正确答案
        return node1;
    }
};
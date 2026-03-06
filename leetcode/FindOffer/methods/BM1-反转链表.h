#include "../include/struct_define.h"

class reverseListSolution {
   public:
    // 解法一：经典迭代法 (双指针) - 时间 O(N), 空间 O(1)
    // 适合在生产环境中使用，防止爆栈
    static ListNode* reverseListIterative(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* post = cur->next;  // 1. 暂存当前节点的下一个节点，以防链表断裂迷路
            cur->next = pre;             // 2. 将当前节点反指向前一个节点 (斩断前缘)
            pre = cur;                   // 3. 将 pre 指针向前移动到当前节点
            cur = post;                  // 4. 将 cur 指针向前移动到之前暂存的 post 节点
        }
        // 当 cur 为空时，pre 正好停留在原链表的最后一个节点，也就是新链表的头节点
        return pre;
    }
    // 解法二：黑魔法递归法 - 时间 O(N), 空间 O(N) (递归调用栈的深度)
    // 能够轻松写出递归反转链表，是彻底搞懂递归的最核心标志
    static ListNode* reverseListRecursive(ListNode* head) {
        // 1. 递归终止条件(Base Case)：
        // 当链表为空，或者链表只有一个节点时，不需要反转，直接返回当前头即可。
        // `head->next == nullptr` 也是我们触底反弹的标志，它能帮我们抓到原链表的尾巴！
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 2. 递 (Dive in)：假设头节点后面的所有节点，都已经被后面的递归函数成功反转了
        // newHead 就是我们一路递下去抓到的那根原链表尾巴（即反转后的新头结点）
        ListNode* newHead = reverseListRecursive(head->next);
        // 3. 归 (Backtrack)：反转当前 head 节点和它后面那个节点的指向关系
        // 此时，head 后面的节点 (head->next) 尚未和 head 断开
        // 我们要让它的 next 重新指回 head
        head->next->next = head;

        // 4. 断开原本 head 指向下一个节点的强关联，防止形成环！
        // 因为 head 现在变成了尾部节点方向，所以它应该指向 nullptr
        head->next = nullptr;
        // 一路把被奉为新王的底层原尾部节点向上传递回去
        return newHead;
    }
};

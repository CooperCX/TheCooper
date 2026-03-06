#include "../include/struct_define.h"

class reverseBetweenSolution {
   public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // 【防御性编程】极个别变态用例中，左边界可能等于右边界，或者链表为空
        if (head == nullptr || m == n) {
            return head;
        }
        // 1. 创建 Dummy 节点，为了防止 new 造成的内存泄漏，这里直接建在栈上更安全！
        // 因为它的生命周期仅在当前函数有效，返回时只返回它的 next 即可。
        ListNode dummy(-1);
        dummy.next = head;

        ListNode* pre = &dummy;
        // 2. 将 pre 移动到待反转区间的前面一个节点
        for (int i = 1; i < m; ++i) {
            pre = pre->next;
        }
        // cur 作为待反转区间的第一个节点，在整个反转过程中物理位置（相对 pre 的逻辑位置）不断后移
        ListNode* cur = pre->next;
        // 3. 开始“穿针引线”式的头插法
        // 【注意循环次数】：总共需要进行 (n - m) 次插拔操作
        for (int i = m; i < n; ++i) {
            // 第一步：把 cur 后面那个需要被插到前面的节点 post 给单独“拎”出来
            ListNode* post = cur->next;
            // 第二步：由于 post 被拔走了，cur 必须和 post 后面的节点接轨，防止链表断开
            cur->next = post->next;
            // 第三步：将 post 强行插到 pre 和 pre 后面原有的节点之间
            post->next = pre->next;

            // 第四步：彻底完成插入，让 pre 链接到这个崭新的“头部”
            pre->next = post;
        }
        // 返回 dummy 节点指向的真正头结点
        return dummy.next;
    }
};
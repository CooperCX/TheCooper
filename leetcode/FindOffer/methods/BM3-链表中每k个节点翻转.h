#include "../include/struct_define.h"

class reverseKGroupSolution {
   public:
    // 解法一：黑盒递归法 (代码最简短，时间 O(N)，空间 O(N/k) 递归深度的栈开销)
    ListNode* reverseKGroupRecursive(ListNode* head, int k) {
        if (head == nullptr || k == 1) return head;

        // 1. 探路阶段：判断剩下的节点到底够不够 k 个
        ListNode* tail = head;
        for (int i = 0; i < k; ++i) {
            // 如果不足 k 个，题目要求保持原有顺序，所以直接返回当前的“头”即可
            if (tail == nullptr) return head;
            tail = tail->next;
        }

        // 2. 反转当前这一组 [head, tail) 的节点 (前闭后开区间)
        ListNode* pre = nullptr;
        ListNode* cur = head;
        // 注意控制条件：反转进行到 tail 就必须停下来！
        while (cur != tail) {
            ListNode* post = cur->next;
            cur->next = pre;
            pre = cur;
            cur = post;
        }

        // 3. 收尾拼接：上述循环结束后，pre 变成了这组反转后的新头结点。
        // 而当初的那个头结点 head 已经被甩到了这组的最后面，成了这组的尾巴。
        // 它该牵谁的手？当然是让下一个完整 K 组的头节点（也就是黑盒递归算出来的老大）跟它牵手。
        head->next = reverseKGroupRecursive(tail, k);

        return pre;  // 向上级返回这个小团体反转后的新头目
    }

    // 解法二：迭代穿针引线法 (空间 O(1)，性能顶配)
    ListNode* reverseKGroupIterative(ListNode* head, int k) {
        if (head == nullptr || k == 1) return head;

        // 1. 创建位于栈上的 Dummy 节点，杜绝内存泄漏
        ListNode dummy(-1);
        dummy.next = head;

        // pre 永远指向准备发生反转的那个小组的【前驱节点】
        ListNode* pre = &dummy;
        // cur 永远指向那个小组的【原头结点】(在头插法中，它在位置上会一直往后退)
        ListNode* cur = head;

        // 只有提前确认身后的节点足够凑齐 K 个，才执行反转
        while (cur != nullptr && check(cur, k)) {
            // 头插法：要在一个小组内反转 K 个节点，总共只需拔插 K - 1 次
            for (int i = 1; i < k; i++) {
                ListNode* post = cur->next;  // 锁定靶点小鸡
                cur->next = post->next;      // 接轨防掉队
                post->next = pre->next;      // 被抓出来的小鸡对准原本的老大后面
                pre->next = post;            // 老鹰牵住它
            }

            // 一轮拔插彻底结束。此时这组的最前面依然连在 pre 后面。
            // 而我们一直苦苦没动的那个 cur，已经被硬生生地挤到了这组的末尾（变成了跟下一个小组交界的节点）！

            // 将 pre 移动到本组最后一个节点 (也就是被挤到末尾的 cur)，准备担任下一组的前驱！
            pre = cur;
            // cur 移动到下一组的原起点，开启下一轮大循环
            cur = cur->next;
        }

        return dummy.next;
    }

   private:
    // 助手函数：探测从 head 起，后面是否还有至少 n 个非空节点
    bool check(ListNode* head, int n) {
        for (int i = 0; i < n; i++) {
            if (head == nullptr) return false;
            head = head->next;
        }
        return true;
    }
};

#include <vector>

#include "../include/struct_define.h"

class isPailSolution {
   public:
    // 解法：快慢指针切分 + 后半段反转验证法
    // 时间复杂度 O(N)，空间复杂度 O(1)
    bool isPail(ListNode* head) {
        if (!head || !head->next) return true;
        // 1. 找中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // 2. 原地反转后半个链表
        // 专门写一个 reverseList 的内部子程序来让主逻辑显得更干净
        ListNode* rightHead = reverseList(slow);

        // 3. 验证回文
        ListNode* p1 = head;
        ListNode* p2 = rightHead;
        bool result = true;  // 先把比对结果存起来！！

        while (p2 != nullptr) {
            if (p1->val != p2->val) {
                result = false;
                break;  // 即便发现不是回文了，也不能直接 return，我们必须恢复现场！
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        // 4. 【高阶工程素养】恢复因验证而导致的链表破坏
        // 也就是把刚才反转的后半段，再反转一次接回去
        reverseList(rightHead);

        return result;
    }

   private:
    // 这里就是被你抽出来的，我们在前几天写过的绝对完美的“翻转链表”代码
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while (cur != nullptr) {
            ListNode* nextTemp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nextTemp;
        }
        return prev;
    }
};
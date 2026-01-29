#include "../include/struct_define.h"

class reverseKGroupSolution {
   public:
    ListNode* reverseKGroupRecursive(ListNode* head, int k) {
        ListNode* tail = head;
        for (int i = 0; i < k; i++) {
            if (nullptr == tail) return head;
            tail = tail->next;
        }

        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur != tail) {
            ListNode* post = cur->next;
            cur->next = pre;
            pre = cur;
            cur = post;
        }
        head->next = reverseKGroupRecursive(tail, k);

        return pre;
    }

    ListNode* reverseKGroupIterative(ListNode* head, int k) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* pre = dummy;
        ListNode* cur = head;

        while (cur != nullptr && check(cur, k)) {
            for (int i = 1; i < k; i++) {
                ListNode* post = cur->next;
                cur->next = post->next;
                post->next = pre->next;
                pre->next = post;
            }
            pre = cur;
            cur = cur->next;
        }

        return dummy->next;
    }

   private:
    bool check(ListNode* head, int n) {
        for (int i = 0; i < n; i++) {
            if (nullptr == head) return false;
            head = head->next;
        }
        return true;
    }
};
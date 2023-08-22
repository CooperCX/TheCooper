#include "../include/struct_define.h"

class reverseKGroupSolution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* tail = head;
        for (int i = 0; i < k; i++) {
            if (tail == nullptr) {
                return head;
            }
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
        head->next = reverseKGroup(tail, k);

        return pre;
    }

    ListNode* reverseKGroup(ListNode* head, int n) {
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;

        ListNode* pre = dummy;
        ListNode* cur = head;

        while (cur != nullptr && check(cur, n)) {
            for (int i = 1; i < n; i++) {
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
        for (int i = 1; i < n; i++) {
            if (head == nullptr) {
                return false;
            }
            head = head->next;
        }
        return true;
    }
};
#include <cstddef>
#include <unordered_set>

#include "../include/struct_define.h"
class hasCycleSolution {
   public:
    bool hasCycle(ListNode *head) {
        std::unordered_set<ListNode *> visited;
        while (head) {
            if (visited.count(head)) return true;
            visited.emplace(head);
            head = head->next;
        }
        return false;
    }

    bool hasCycleTwoPointer(ListNode *head) {
        if (nullptr == head || nullptr == head->next) return false;

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
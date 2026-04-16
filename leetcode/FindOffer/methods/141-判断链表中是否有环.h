#include <cstddef>
#include <unordered_set>

#include "../include/struct_define.h"
class hasCycleSolution {
   public:
    bool hasCycle(ListNode *head) {
        // 准备一个本子（哈希集合），专门记录我们踩过的节点的内存地址
        std::unordered_set<ListNode *> visited;

        while (head) {
            // 翻一翻本子，如果当前节点在里面，说明绕圈了！
            if (visited.count(head)) return true;

            // 如果没在里面，就把当前节点记在本子上
            // 使用 emplace 比 insert 效率略高一点点（C++11 原地构造特性）
            visited.emplace(head);

            // 往下走一步
            head = head->next;
        }

        // 如果能安稳地走到 nullptr，说明链表是有尽头的，肯定没环
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
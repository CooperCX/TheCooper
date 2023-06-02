#include <unordered_map>
#include "struct_define.h"

class Solution {
public:
    // 快慢指针
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        if (pHead == nullptr || pHead->next == nullptr) {
            return nullptr;
        }
        ListNode* fast = pHead, * slow = pHead;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                break;
            }
        }
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }
        slow = pHead;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }

    // 借助哈希表
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        if (pHead == nullptr || pHead->next == nullptr) {
            return nullptr;
        }
        std::unordered_map<ListNode*, int> visited;
        while (pHead) {
            visited[pHead]++;
            if (visited[pHead] == 2) {
                break;
            }
            pHead = pHead->next;
        }
        return pHead;
    }
};
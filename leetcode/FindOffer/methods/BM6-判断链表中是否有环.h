#include <unordered_map>
#include "../include/struct_define.h"
class hasCycleSolution {
public:
    bool hasCycle(ListNode *head) {
        std::unordered_map<ListNode*, int> hash;
        while (head != nullptr) {
            hash[head]++;
            head = head->next;
            if (hash[head] > 1) {
                return true;
            }
        }
        return false;
    }
};
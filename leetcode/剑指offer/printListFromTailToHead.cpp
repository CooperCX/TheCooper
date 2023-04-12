#include <vector>
#include <algorithm>
#include "struct_define.h"

class Solution {
public:
    std::vector<int> printListFromTailToHead(ListNode* head) {
        std::vector<int> results;
        if (head == nullptr) {
            return results;
        }
        while(head != nullptr) {
            results.emplace_back(head->val);
            head = head->next;
        }
        reverse(results.begin(), results.end());
        return results;
    }
};

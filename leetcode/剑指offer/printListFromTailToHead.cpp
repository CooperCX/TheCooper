#include <vector>
#include <algorithm>
struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;

    ListNode(int v, ListNode* p) : val(v), next(p) {}
};

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

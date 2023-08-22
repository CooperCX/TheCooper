#include "../include/struct_define.h"
#include <vector>

class isPailSolution {
public:

    bool isPail(ListNode* head) {
        // write code here
        std::vector<int> numbers;
        while (head != nullptr) {
            numbers.push_back(head->val);
            head = head->next;
        }
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            if (numbers[left] != numbers[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};
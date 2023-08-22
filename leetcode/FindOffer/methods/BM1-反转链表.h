#include "../include/struct_define.h"

class reverseListSolution {
public:
    /*迭代*/
    static ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* post = cur->next;  // 记录后一节点
            cur->next = pre;  // 前一节点<-当前节点
            pre = cur;  // 当前节点变为前一节点
            cur = post; // 后一节点变为当前节点
        }
        return pre;
    }
};

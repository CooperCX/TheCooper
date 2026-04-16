#include "../include/struct_define.h"

class deleteDuplicates1Solution {
   public:
    // 解法：单指针遍历删除法（利用已排序特性）
    // 时间复杂度 O(N)，空间复杂度 O(1)
    ListNode* deleteDuplicates(ListNode* head) {
        // 【防御性编程】空链表或只有一个节点的链表，绝对不可能有重复
        if (!head || !head->next) return head;
        ListNode* cur = head;
        // 因为我们要安全地探测下一个节点 cur->next 的值，
        // 所以不仅 cur 本身不能为 null，cur->next 也绝对不能为 null
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->val == cur->next->val) {
                // 如果发现下一个节点是自己的克隆人，干掉下一个节点！
                ListNode* duplicateNode = cur->next;  // 揪住克隆人
                cur->next = cur->next->next;          // 把指针越过他
                delete duplicateNode;                 // 【高阶素养】手动释放堆内存，防止泄露

                // 【注意】这里干掉克隆人后，千万不能写 cur = cur->next;
                // 因为下下个节点也可能还是一个克隆人（例如：1 -> 1 -> 1）
                // 必须留在原地，迎接下一个过来的新兄弟继续验明正身！
            } else {
                // 如果新来的兄弟和自己不一样，就放心大胆地往前走
                cur = cur->next;
            }
        }
        return head;  // 头节点绝对不受波及，安全返回
    }
};
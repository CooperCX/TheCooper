#include "../include/struct_define.h"

class deleteDuplicates2Solution {
   public:
    // 解法：Dummy节点 + 前驱探测法 (连坐追杀)
    // 时间复杂度 O(N)，只遍历一遍；空间 O(1)
    ListNode* deleteDuplicates(ListNode* head) {
        // 【防御】0 个或 1 个节点绝对不会有结党营私的重复现象
        if (!head || !head->next) return head;
        // 【套路】因为真正的 head 有可能也参与重复被杀掉，所以必须要建个庇护所
        ListNode dummy(-1);
        dummy.next = head;
        // pre 指针永远站在被考察节点的前一个安全屋里
        ListNode* pre = &dummy;
        // 只要预见到的未来至少还有两个人 (才有重名的犯罪条件)
        while (pre->next != nullptr && pre->next->next != nullptr) {
            // 探子回报：前面两个人竟然是同名的！
            if (pre->next->val == pre->next->next->val) {
                // 记下通缉犯的名字
                int duplicateVal = pre->next->val;

                // 开启连坐大清洗：只要前面的人还在，并且名字就在通缉令上，格杀勿论！
                while (pre->next != nullptr && pre->next->val == duplicateVal) {
                    ListNode* nodeToDelete = pre->next;
                    // 断开锁链
                    pre->next = nodeToDelete->next;  // 或者等于 pre->next->next
                    // 彻底销毁
                    delete nodeToDelete;
                }

                // 【精髓】大清洗结束后，pre 自己千万不能动！
                // 因为新接上来的那一拨人 (虽然现在名字不叫 duplicateVal 了)，
                // 但他们内部可能还是另一批同名克隆人！必须让 while 外循环再审他们一次。

            } else {
                // 如果前面两个人名字不一样，说明最前面那个人是良民。
                // 赐予安全屋，pre 向前推进一步，继续考察下一批。
                pre = pre->next;
            }
        }
        // dummy 的下一个是谁，谁就是清洗后大难不死的真正元老
        return dummy.next;
    }
};
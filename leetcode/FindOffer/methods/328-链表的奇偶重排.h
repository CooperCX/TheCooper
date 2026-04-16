#include "../include/struct_define.h"

class oddEvenListSolution {
   public:
    // 解法：双指针交替分离法
    // 时间复杂度 O(N)，空间复杂度 O(1)
    ListNode* oddEvenList(ListNode* head) {
        // 【防御性编程】没有节点，或者只有 1 个、2 个节点时，怎么排都是原样，直接返回
        if (!head || !head->next || !head->next->next) return head;
        ListNode* odd = head;              // 奇数大军的游标 (从第 1 个节点开始)
        ListNode* even_head = head->next;  // 死死留住偶数大军的王座，以备最后会师
        ListNode* even = even_head;        // 偶数大军的游标 (从第 2 个节点开始)
        // 只要跑在最前面的 even 且 even->next 还在，就说明后面还有奇数节点可以跳！
        while (even != nullptr && even->next != nullptr) {
            // 奇数节点跳过中间的这个偶数
            odd->next = even->next;
            odd = odd->next;
            // 偶数节点跳过刚刚那个奇数
            even->next = odd->next;
            even = even->next;
        }
        // 奇数大军走到尽头，把偶数大军的王座接到自己屁股后面
        odd->next = even_head;
        return head;  // 头节点永远是原始的奇数头，它是绝对安全的
    }
};
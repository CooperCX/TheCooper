#include <cstddef>
#include <stack>

#include "206-反转链表.h"

class addInListSolution {
   public:
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        head1 = reverseListSolution::reverseListIterative(head1);
        head2 = reverseListSolution::reverseListIterative(head2);

        ListNode* resNode = nullptr;
        int carry = 0;

        while (head1 || head2 || carry) {
            int sum = carry + (head1 ? head1->val : 0) + (head2 ? head2->val : 0);
            carry = sum / 10;

            // 头插法
            ListNode* newNode = new ListNode(sum % 10);
            newNode->next = resNode;
            resNode = newNode;

            if (head1) head1 = head1->next;
            if (head2) head2 = head2->next;
        }

        return resNode;
    }

    // 解法：双栈法 (不破坏原链表结构，完美应对倒序加法)
    // 时间复杂度 O(max(M, N))，空间复杂度 O(M + N) 用于存栈
    ListNode* addInList2(ListNode* head1, ListNode* head2) {
        std::stack<int> s1, s2;
        // 1. 将两个链表的值全部压入各自的栈中
        while (head1 != nullptr) {
            s1.push(head1->val);
            head1 = head1->next;
        }
        while (head2 != nullptr) {
            s2.push(head2->val);
            head2 = head2->next;
        }
        // 进位标识符
        ListNode* resNode = nullptr;
        int carry = 0;
        // 2. 只要两个栈有任何一个没空，或者最后还有进位，我们就继续抽数字
        // 这里的逻辑和你写的“大数加法 (BM86)” 以及前几题如出一辙！
        while (!s1.empty() || !s2.empty() || carry != 0) {
            // 优雅提取：有货就弹栈取值，没货当 0 处理
            int x = 0;
            if (!s1.empty()) {
                x = s1.top();
                s1.pop();
            }

            int y = 0;
            if (!s2.empty()) {
                y = s2.top();
                s2.pop();
            }
            // 计算当前位的和与进位
            int sum = x + y + carry;
            carry = sum / 10;

            // 3. 【核心技巧】头插法构建结果链表 (让先算出的低位不断往后挤)
            ListNode* newNode = new ListNode(sum % 10);
            newNode->next = resNode;
            resNode = newNode;  // 更新最新的头结点
        }
        return resNode;
    }
};
#include <queue>
#include <vector>

#include "21-合并两个排序链表.h"  // 假设里面有 mergeListSolution::mergeList

class mergeKListsSolution {
   public:
    // 解法一：分治法 (Divide and Conquer) - 时间 O(N log K), 空间 O(log K) 栈深度
    ListNode* mergeKListsDivideConquer(std::vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeKListsCore(lists, 0, lists.size() - 1);
    }

   private:
    // 分治法的核心辅助函数：只管把 [start, end] 区间内的所有链表合并出来
    ListNode* mergeKListsCore(std::vector<ListNode*>& lists, int start, int end) {
        // 递归终止条件
        if (start > end) {
            return nullptr;
        } else if (start == end) {
            return lists[start];  // 只剩一条链表，直接返回它自己
        } else {
            // 这就是经典归并排序的二分逻辑：
            // 找中点，左边大军去打出一统天下的链表，右边大军也打出一统天下的链表
            int mid = start + (end - start) / 2;
            ListNode* leftMerged = mergeKListsCore(lists, start, mid);
            ListNode* rightMerged = mergeKListsCore(lists, mid + 1, end);

            // 两路大军会师！调用 BM4 里的两个有序链表合并 API 决出最终霸主
            return mergeListSolution::mergeList(leftMerged, rightMerged);
        }
    }

   public:
    // 解法二：优先队列/最小堆法 (Priority Queue) - 时间 O(N log K), 空间 O(K) 堆大小
    // 这个解法在处理数据流很大、链表极长但 K 固定时非常常用！
    ListNode* mergeKListsMinHeap(std::vector<ListNode*>& lists) {
        ListNode dummy(-1);
        ListNode* tail = &dummy;

        // 【语法点】定义优先级队列，类型是 ListNode*，容器是 vector，比较器是我们上面写的 compareListNode
        std::priority_queue<ListNode*, std::vector<ListNode*>, compareListNode> pq;

        // 1. 初始化小根堆：把所有链表的【头结点】(各链表当前最小的节点) 塞进堆里
        for (ListNode* head : lists) {
            if (head != nullptr) {
                pq.push(head);
            }
        }

        // 2. 只要堆里还有神仙打架，我们就一直抽最小的出来
        while (!pq.empty()) {
            // 选出堆顶老大哥 (K 个头里最小的那一个)
            ListNode* node = pq.top();
            pq.pop();  // 大哥离职去了新链表

            // 把它挂在结果链表的尾巴上
            tail->next = node;
            tail = tail->next;

            // 【最精妙的一步】：大哥离职后，如果大哥的队伍里还有小弟，把头号小弟推进堆里，继续参与全国总决赛！
            if (node->next != nullptr) {
                pq.push(node->next);
            }
        }

        return dummy.next;
    }
};

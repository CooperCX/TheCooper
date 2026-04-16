/*复杂链表的深拷贝*/

#include <unordered_map>
#include "../include/struct_define.h"

class copyRandomListNodeSolution {
public:
    std::unordered_map<RandomListNode*, RandomListNode*> ump;
public:
    /*哈希表迭代*/
    RandomListNode* iteralClone(RandomListNode* pHead) {
        if (pHead == nullptr) {
            return nullptr;
        }
        for (auto p = pHead; p != nullptr; p = p->next) {
            ump[p] = new RandomListNode(p->val);
        }
        for (auto p = pHead; p != nullptr; p = p->next) {
            ump[p]->next = ump[p->next];
            ump[p]->random = ump[p->random];
        }
        return ump[pHead];
    }
    /*哈希表递归*/
    RandomListNode* recursiveClone(RandomListNode* pHead) {
        if (pHead == nullptr) {
            return nullptr;
        }
        auto newHead = new RandomListNode(pHead->val);
        ump[pHead] = newHead;
        newHead->next = recursiveClone(pHead->next);
        if (pHead->random) {
            newHead->random = ump[pHead->random];
        }
        return newHead;
    }
};
#pragma once

#include <vector>
/*链表节点*/
struct ListNode {
    int val = 0;
    ListNode* next = nullptr;
    ListNode(int val) : val(val), next(nullptr) {}
};

struct compareListNode {
    bool operator()(ListNode* a, ListNode* b) { return a->val > b->val; }
};

/*复杂链表节点*/
struct RandomListNode {
    int val;
    RandomListNode* next = nullptr;
    RandomListNode* random = nullptr;

    RandomListNode(int v) : val(v), next(nullptr), random(nullptr) {}
};

/*二叉树节点*/
struct TreeNode {
    int val = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

struct TreeLinkNode {
    int val;
    TreeLinkNode* left;
    TreeLinkNode* right;
    TreeLinkNode* next;
    TreeLinkNode(int val) : val(val), left(nullptr), right(nullptr), next(nullptr) {}
};

struct Node {
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val) { val = _val; }

    Node(int _val, std::vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

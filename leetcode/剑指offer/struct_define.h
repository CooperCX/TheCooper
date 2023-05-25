/*链表节点*/
struct ListNode
{
    int val;
    ListNode* next = nullptr;

    ListNode(int v) : val(v), next(nullptr) {}
};

/*复杂链表节点*/
struct RandomListNode
{
    int val;
    RandomListNode* next = nullptr;
    RandomListNode* random = nullptr;

    RandomListNode(int v) : val(v), next(nullptr), random(nullptr) {}
};

/*二叉树节点*/
struct TreeNode
{
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    TreeNode(int val) :
        val(val), left(nullptr), right(nullptr) {}
};
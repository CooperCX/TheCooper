#include <vector>

// 多叉树节点定义
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}
    Node(int _val) : val(_val) {}
    Node(int _val, std::vector<Node*> _children) : val(_val), children(_children) {}
};

class Solution {
public:
    /**
     * @brief 查找多叉树中两个节点的最近公共祖先 (LCA)
     *
     * @param root 多叉树的根节点
     * @param p 节点 1
     * @param q 节点 2
     * @return Node* 最近公共祖先节点
     */
    Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        // 如果根节点为空，或者遇到了 p 或是 q，直接返回当前节点
        if (root == nullptr || root == p || root == q) return root;

        Node* lca = nullptr;
        int count = 0;  // 记录在子树中找到目标节点的次数

        // 递归遍历所有子节点
        for (Node* child : root->children) {
            Node* res = lowestCommonAncestor(child, p, q);
            if (res != nullptr) {
                count++;
                lca = res;
            }
        }

        // 如果在两棵不同的子树中分别找到了 p 和 q，说明当前 root 就是最近公共祖先
        if (count == 2) {
            return root;
        }

        // 否则返回非空的 lca（如果 count == 1 说明 p 或 q 在某棵子树中；如果 count == 0 说明都没找到，lca 为 nullptr）
        return lca;
    }
};

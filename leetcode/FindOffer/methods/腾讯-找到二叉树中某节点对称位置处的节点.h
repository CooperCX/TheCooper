#pragma once
#include <algorithm>
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

// 二叉树结构
struct TreeNode {
    int val = 0;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;

    TreeNode(int val) : val(val), leftChild(nullptr), rightChild(nullptr) {}
};

// 二叉树的层序遍历
inline std::vector<std::vector<TreeNode*>> levelOrder(TreeNode* root) {
    std::vector<std::vector<TreeNode*>> results;
    if (nullptr == root) return results;

    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        std::vector<TreeNode*> temp;
        int len = q.size();
        while (len > 0) {
            TreeNode* node = q.front();
            temp.push_back(node);
            q.pop();
            len--;
            if (node->leftChild) q.push(node->leftChild);
            if (node->rightChild) q.push(node->rightChild);
        }
        results.push_back(temp);
    }
    return results;
}

// 二叉树的镜像翻转
inline void mirrorCore(TreeNode* root) {
    if (nullptr == root) {
        return;
    }
    std::swap(root->leftChild, root->rightChild);
    mirrorCore(root->leftChild);
    mirrorCore(root->rightChild);
}

// 如果不允许使用递归（防止栈溢出）
inline void mirrorCoreIterative(TreeNode* root) {
    if (nullptr == root) {
        return;
    }
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        std::swap(node->leftChild, node->rightChild);
        if (node->leftChild) q.push(node->leftChild);
        if (node->rightChild) q.push(node->rightChild);
    }
}

// 找到二叉树中某节点的对称位置节点
inline TreeNode* findSymmetricalRecursive(TreeNode* p1, TreeNode* p2, TreeNode* node) {
    if (nullptr == p1 || nullptr == p2) {
        return nullptr;
    }

    if (node == p1) {
        return p2;
    }
    if (node == p2) {
        return p1;
    }

    TreeNode* res = findSymmetricalRecursive(p1->leftChild, p2->rightChild, node);
    if (nullptr != res) return res;
    return findSymmetricalRecursive(p1->rightChild, p2->leftChild, node);
}

inline TreeNode* findSymmetrical(TreeNode* root, TreeNode* node) {
    return findSymmetricalRecursive(root, root, node);
}

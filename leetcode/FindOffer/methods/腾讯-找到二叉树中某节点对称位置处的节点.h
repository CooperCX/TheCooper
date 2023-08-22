#include <vector>
#include <algorithm>
#include <queue>

struct TreeNode
{
    int val;
    TreeNode* leftChild = nullptr;
    TreeNode* rightChild = nullptr;

    TreeNode(int val) :
        val(val), leftChild(nullptr), rightChild(nullptr)
    {
    }
};

std::vector<std::vector<TreeNode*>> levelOrder(TreeNode* root) {
    std::vector<std::vector<TreeNode*>> results;
    if (root == nullptr) {
        return results;
    }
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
            q.push(node->leftChild);
            q.push(node->rightChild);
        }
        results.push_back(temp);
    }
    return results;
}

void MirrorCore(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    TreeNode* temp = root->leftChild;
    root->leftChild = root->rightChild;
    root->rightChild = temp;
    MirrorCore(root->leftChild);
    MirrorCore(root->rightChild);
}

TreeNode* Mirror(TreeNode* root) {
    MirrorCore(root);
    return root;
}

TreeNode* findSymmetrical(TreeNode* root, TreeNode* node) {
    std::vector<std::vector<TreeNode*>> inorderVector1 = levelOrder(root);
    int row = 0, col = 0;
    for (int i = 0; i < inorderVector1.size(); i++) {
        for (int j = 0; j < inorderVector1[i].size(); j++) {
            if (inorderVector1[i][j] == node) {
                row = i;
                col = j;
            }
        }
    }

    TreeNode* mirrorRoot = Mirror(root);
    std::vector<std::vector<TreeNode*>> inorderVector2 = levelOrder(mirrorRoot);
    return inorderVector2[row][col];
}

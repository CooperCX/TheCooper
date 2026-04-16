#include <queue>

#include "../include/struct_define.h"

inline int maxDepthDFS(Node* root) {
    if (!root) return 0;

    int max_depth = 1;
    for (int i = 0; i < root->children.size(); ++i) {
        max_depth = std::max(max_depth, maxDepthDFS(root->children[i]) + 1);
    }

    return max_depth;
}

inline int maxDepthBFS(Node* root) {
    if (!root) return 0;

    std::queue<Node*> q;
    q.push(root);

    int max_depth = 0;
    while (!q.empty()) {
        int curr_size = q.size();
        for (int i = 0; i < curr_size; ++i) {
            Node* node = q.front();
            q.pop();

            for (Node* child : node->children) {
                q.push(child);
            }
        }
        max_depth++;
    }

    return max_depth;
}
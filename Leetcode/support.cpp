#include "support.h"

#include <queue>

TreeNode* createTree(const std::vector<int>& data) {
    if (data.empty() && data[0] == NULL_VALUE) return nullptr;
    TreeNode* root = new TreeNode(data[0]);
    std::queue<TreeNode*> nodes;
    nodes.push(root);
    int i = 1;
    while (!nodes.empty()) {
        TreeNode* node = nodes.front();
        nodes.pop();
        if (i == data.size()) break;
        int v = data[i++];
        if (v != NULL_VALUE) nodes.push(node->left = new TreeNode(v));

        if (i == data.size()) break;
        v = data[i++];
        if (v != NULL_VALUE) nodes.push(node->right = new TreeNode(v));
    }

    return root;

}

void destroyTree(TreeNode* root) {
    if (root == nullptr) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}
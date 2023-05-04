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

FileUtil::FileUtil() : ifs("E:\\data.txt") {

}

FileUtil::~FileUtil() {

}

void FileUtil::ReadIntVector(vector<int>& out, bool tag) {
    if (!tag) {
        ReadChar(); // [
    }
    char sep;
    int value = 0;
    do {
        ifs >> value;
        out.push_back(value);
        sep = ReadChar();
    } while (sep != ']');
}

void FileUtil::ReadIntVectorVector(vector<vector<int>>& out) {
    ReadChar();
    char ch = ReadChar(); // [
    while (ch == '[') {
        out.push_back({});
        ReadIntVector(out.back(), true);
        ch = ReadChar();
        if (ch == ']') break;
        ch = ReadChar(); // [
    }

}

char FileUtil::ReadChar() {
    char ch = 0;
    do {
        ifs >> ch;
    } while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
    return ch;
}

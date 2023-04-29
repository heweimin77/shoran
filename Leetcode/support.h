#ifndef __SUPPORT_H__
#define __SUPPORT_H__

#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

constexpr int NULL_VALUE = INT_MIN;
constexpr int null = INT_MIN;

TreeNode* createTree(const std::vector<int> &data);
void destroyTree(TreeNode* root);

#endif
#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int amountOfTime(TreeNode *root, int start)
    {
        vector<vector<int>> adjs(start + 1);
        traverse(root, adjs);
        vector<bool>  visited(adjs.size());
        queue<int> q;
        q.push(start);
        visited[start] = true;
        int result = 0;
        while (!q.empty()) {
            ++result;
            for (int i = q.size(); i > 0; --i) {
                int now = q.front();
                q.pop();
                for (auto next : adjs[now]) {
                    if (visited[next]) continue;
                    visited[next] = true;
                    q.push(next);
                }
                //cout << now << " ";
            }
            cout << endl;
        }
        return result - 1;
    }
    void traverse(TreeNode *node, vector<vector<int>> &adjs)
    {
        TreeNode *cnode = nullptr;
        if (node->left) {
            cnode = node->left;
            int x = max(cnode->val, node->val);
            if (x >= adjs.size()) {
                adjs.resize(x + 1);
            }
            adjs[cnode->val].push_back(node->val);
            adjs[node->val].push_back(cnode->val);
            traverse(cnode, adjs);
        }
        if (node->right) {
            cnode = node->right;
            int x = max(cnode->val, node->val);
            if (x >= adjs.size()) {
                adjs.resize(x + 1);
            }
            adjs[cnode->val].push_back(node->val);
            adjs[node->val].push_back(cnode->val);
            traverse(cnode, adjs);
        }
    }
};

class TestSolution :public testing::Test {
public:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }
};

TEST_F(TestSolution, Test1)
{
    TreeNode *root = createTree({ 1 });
    Solution s;
    auto actual = s.amountOfTime(root, 1);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
}

}


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
    int maxSumBST(TreeNode *root)
    {
        bool ok = true;
        pair<int, int> range;
        return maxsum(root, ok, range).first;
    }
    pair<int,int>  maxsum(TreeNode *node, bool &ok, pair<int,int> &range)
    {
        if (node == nullptr) {
            ok = true;
            range = { INT_MAX, INT_MIN };
            return { 0, 0 };
        }

        bool lok = true, rok = true;
        pair<int, int> lrange, rrange;
        auto lr = maxsum(node->left, lok, lrange);
        auto rr = maxsum(node->right, rok, rrange);
        if (lok && rok && lrange.second < node->val && node->val < rrange.first) {
            ok = true;
            range.first = lrange.first == INT_MAX ? node->val : lrange.first;
            range.second = rrange.second == INT_MIN ? node->val : rrange.second;
            int fr = max(lr.first, rr.first);
            int sr = lr.second + rr.second + node->val;
            return { max(fr, sr), sr };
        } else {
            ok = false;
            return { max(lr.first, rr.first), 0 };
        }
            
    }
    
};

class TestSolution :public testing::Test
{
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
    //TreeNode *root = createTree({ 3,2,5,null,null,4,6});
    TreeNode *root = createTree({ 1,4,3,2,4,2,5,null,null,null,null,null,null,4,6});
    Solution s;
    auto actual = s.maxSumBST(root);
    decltype(actual) expect = 20;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, Test2)
{
    TreeNode *root = createTree({ 4,3,null,1,2 });
    Solution s;
    auto actual = s.maxSumBST(root);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    TreeNode *root = createTree({ 8,9,8,null,9,null,1,null,null,-3,5,null,-2,null,6 });
    Solution s;
    auto actual = s.maxSumBST(root);
    decltype(actual) expect = 11;
    EXPECT_EQ(expect, actual);
}

}

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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int result = 0;
        int n = favorite.size();
        vector<int> colors(n);

        function<void(int, int)> dfs = [&](int now, int level) {
            if (colors[now] < 0) return;
            if (colors[now] > 0) {
                result = max(result, level - colors[now]);
                colors[now] = -1;
                return;
            }
            colors[now] = level;
            dfs(favorite[now], level + 1);
            colors[now] = -1;
        };

        for (int i = 0; i < n; ++i) {
            if (colors[i] == 0) dfs(i, 1);
        }

        return result;
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


TEST_F(TestSolution, TestMain)
{
    vector<int> favorite = { 2,2,1,2 };
    Solution s;
    auto actual = s.maximumInvitations(favorite);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

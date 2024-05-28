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
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        vector<int> qindexes(queries.size());
        iota(qindexes.begin(), qindexes.end(), 0);
        sort(qindexes.begin(), qindexes.end(), [&](const int lhs, const int rhs) {
            return max(queries[lhs][0], queries[lhs][1]) > max(queries[rhs][0], queries[rhs][1]);
            });

        vector<int> results(queries.size());
        vector<pair<int, int>> iresults;
        int i = heights.size() - 1;
        for (auto index : qindexes) {
            auto& q = queries[index];
            int hi = max(q[0], q[1]);
            int li = min(q[0], q[1]);
            for (; i >= hi; --i) {
                int h = heights[i];
                while (!iresults.empty() && iresults.back().first <= h) iresults.pop_back();
                iresults.emplace_back(h, i);
            }
            if (q[0] == q[1]) {
                results[index] = hi;
                continue;
            }

            int hmax = max(heights[q[0]], heights[q[1]]);
            if (heights[li] < hmax) {
                results[index] = hi;
                continue;
            }
            auto it = lower_bound(iresults.begin(), iresults.end(), pair<int, int>(hmax, INT_MAX), greater<pair<int, int>>());
            if (it == iresults.begin()) results[index] = -1;
            else {
                --it;
                results[index] = it->second;
            }

        }
        return results;
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
    vector<int> heights = { 6,4,8,5,2,7 };
    vector<vector<int>> queries = { {0,1}, {0,3}, {2,4}, {3,4}, {2,2} };
    Solution s;
    auto actual = s.leftmostBuildingQueries(heights, queries);
    decltype(actual) expect = { 2,5,-1,5,2 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<int> heights = { 1,2,1,2,1,2 };
    vector<vector<int>> queries = { {0,2}};
    Solution s;
    auto actual = s.leftmostBuildingQueries(heights, queries);
    decltype(actual) expect = { 3 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> heights = { 5,3,8,2,6,1,4,6 };
    vector<vector<int>> queries = { {5,2} };
    Solution s;
    auto actual = s.leftmostBuildingQueries(heights, queries);
    decltype(actual) expect = { -1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}

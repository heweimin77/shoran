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
    int maxMoves(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<int> nows;
        for (int i = 0; i < m; ++i) nows.push_back(i);
        for (int j = 0; j < n - 1; ++j) {
            vector<int> nexts;
            for (auto now : nows) {
                int nv = grid[now][j];
                if (now > 0 && grid[now - 1][j + 1] > nv) {
                    if (nexts.empty() || nexts.back() != now - 1) {
                        nexts.push_back(now - 1);
                    }
                }
                if (grid[now][j + 1] > nv) {
                    if (nexts.empty() || nexts.back() != now) {
                        nexts.push_back(now);
                    }
                }
                if (now + 1 < m && grid[now + 1][j + 1] > nv) {
                    nexts.push_back(now + 1);
                }
            }
            if (nexts.empty()) return j;
            nows = nexts;
        }
        return n - 1;
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
    vector<vector<int>> grid = { {2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15} };
    Solution s;
    auto actual = s.maxMoves(grid);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

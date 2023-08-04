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
    int uniquePathsIII(vector<vector<int>>& grid) {
        int count = 0;
        pair<int, int> start = { 0, 0 };
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == -1) {
                    ++count;
                } else if (grid[i][j] == 1) {
                    start = { i, j };
                }
            }
        }
        count = m * n - count;
        result = 0;
        traverse(grid, start, count);
        return result;
    }
    void traverse(vector<vector<int>>& grid, const pair<int, int> &now, int count) {
        if (--count == 0) {
            ++result;
            return;
        }
        if (grid[now.first][now.second] == 2) {
            return;
        }
        grid[now.first][now.second] = -10;
        int delta[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        for (auto& d : delta) {
            pair<int, int> next = { now.first + d[0], now.second + d[1] };
            if (next.first < 0 || next.first >= grid.size()) continue;
            if (next.second < 0 || next.second >= grid[0].size()) continue;
            if (grid[next.first][next.second] < 0) continue;
            traverse(grid, next, count);
        }
        grid[now.first][now.second] = 0;
    }
private:
    int result = 0;
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
    vector<vector<int>> grid = { {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1} };
    Solution s;
    auto actual = s.uniquePathsIII(grid);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}

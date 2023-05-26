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
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[n - 1][n - 1] != 0 || grid[0][0] != 0) return -1;
        if (n == 1) return 1;
        vector<vector<int>> results(n, vector<int>(n));
        queue<pair<int, int>> q;
        results[n - 1][n - 1] = 1;
        q.push({ n - 1, n - 1 });
        int deltas[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1},  {1, -1}, {1, 0}, {1, 1} };
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int nv = results[now.first][now.second] + 1;
            for (auto& d : deltas) {
                pair<int, int> next = { now.first + d[0], now.second + d[1] };
                if (next.first < 0 || next.first >= n) continue;
                if (next.second < 0 || next.second >= n) continue;
                if (grid[next.first][next.second] != 0) continue;
                if (results[next.first][next.second] != 0) continue;
                results[next.first][next.second] = nv;
                if (next.first == 0 && next.second == 0) return nv;
                q.push(next);
            }
        }

        return -1;
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
    vector<vector<int>> grid = { {0, 1},{1, 0} };
    Solution s;
    auto actual = s.shortestPathBinaryMatrix(grid);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

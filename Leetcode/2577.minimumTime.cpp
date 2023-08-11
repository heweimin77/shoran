#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>

#include "support.h"

using namespace std;

namespace {

class Solution {
#define MAKE_POS(x, y) (((x) << 16) | (y))
#define GET_X(pos)  ((pos) >> 16)
#define GET_Y(pos)   ((pos) & 0xFFFF)
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) return -1;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((grid[i][j] & 1) != ((i + j) & 1)) {
                    ++grid[i][j];
                }
            }
        }
        vector<vector<int>> results(m, vector<int>(n, -1));
        results[0][0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({ 0, MAKE_POS(0, 0) });
        int delta[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            int x = GET_X(now.second);
            int y = GET_Y(now.second);
            if (x == m - 1 && y == n - 1) return now.first;
            if (now.first > results[x][y]) continue;
            cout << "now: " << x << ", " << y << ": " << now.first << endl;
            for (auto d : delta) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || nx >= m) continue;
                if (ny < 0 || ny >= n) continue;
                int nv = max(now.first + 1, grid[nx][ny]);
                if (results[nx][ny] < 0 || nv < results[nx][ny]) {
                    results[nx][ny] = nv;
                    q.push({ nv, MAKE_POS(nx, ny) });
                    cout << "    next: " << nx << ", " << ny << ": " << nv << endl;
                }
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
    vector<vector<int>> grid = { {0,1,3,2}, {5,1,2,5}, {4,3,8,6} };
    Solution s;
    auto actual = s.minimumTime(grid);
    decltype(actual) expect = 7;
    EXPECT_EQ(expect, actual);
}
}

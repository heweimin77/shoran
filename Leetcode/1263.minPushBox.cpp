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
#define MAKE_STATE(x, y, d) ((x) | ((y) << 8) | ((d) << 16))
#define GET_X(state) ((state) & 0xFF)
#define GET_Y(state) (((state) >> 8) & 0xFF)
#define GET_D(state) (((state) >> 16) & 0xFF)
#define IS_SAME(s1, s2)  (((s1) & 0xFFFF) == ((s2) & 0xFFFF))


public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        unsigned s = 0, b = 0, t = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    s = MAKE_STATE(i, j, 0);
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'T') {
                    t = MAKE_STATE(i, j, 0);
                    grid[i][j] = '.';
                } else if (grid[i][j] == 'B') {
                    b = MAKE_STATE(i, j, 0);
                    grid[i][j] = '.';
                }
            }
        }
        vector<unsigned> ns = getValidState(grid, b, s);
        unordered_map<unsigned, int> results;
        queue<unsigned> q;
        for (auto s : ns) {
            results[s] = 0;
            q.push(s);
        }
        int delta[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int x = GET_X(now), y = GET_Y(now), d = GET_D(now);
            int nx = x + delta[d][0], ny = y + delta[d][1];
            int v = results[now] + 1;
            if (nx < 0 || nx >= m) continue;
            if (ny < 0 || ny >= n) continue;
            if (grid[nx][ny] == '#') continue;
            b = MAKE_STATE(nx, ny, 0);
            s = MAKE_STATE(x, y, 0);
            if (b == t) {
                return v;
            }
            ns = getValidState(grid, b, s);
            for (auto s : ns) {
                if (results.count(s) == 0) {
                    results[s] = v;
                    q.push(s);
                }
            }
        }
        return -1;
    }
    vector<unsigned> getValidState(vector<vector<char>>& grid, unsigned b, unsigned s) {
        int m = grid.size(), n = grid[0].size();
        int delta[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        vector<unsigned> results;
        int bx = GET_X(b), by = GET_Y(b);
        grid[bx][by] = '#';
        vector<vector<bool>> connected(m, vector<bool>(n));
        queue<unsigned> q;
        connected[GET_X(s)][GET_Y(s)] = true;
        q.push(s);
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int x = GET_X(now), y = GET_Y(now);
            for (auto& d : delta) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= m) continue;
                if (ny < 0 || ny >= n) continue;
                if (grid[nx][ny] == '#') continue;
                if (connected[nx][ny]) continue;
                connected[nx][ny] = true;
                q.push(MAKE_STATE(nx, ny, 0));
            }
        }
        for (int d = 0; d < 4; ++d) {
            int nx = bx + delta[d][0], ny = by + delta[d][1];
            if (nx < 0 || nx >= m) continue;
            if (ny < 0 || ny >= n) continue;
            if (!connected[nx][ny]) continue;
            results.push_back(MAKE_STATE(bx, by, d ^ 2));
        }

        grid[bx][by] = '.';
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

TEST_F(TestSolution, TestMain)
{
    vector<vector<char>> grid = {{'#', '#', '#', '#', '#', '#'},
        {'#', 'T', '#', '#', '#', '#'},
        {'#', '.', '.', 'B', '.', '#'},
        {'#', '.', '#', '#', '.', '#'},
        {'#', '.', '.', '.', 'S', '#'},
        {'#', '#', '#', '#', '#', '#'}};
    Solution s;
    auto actual = s.minPushBox(grid);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

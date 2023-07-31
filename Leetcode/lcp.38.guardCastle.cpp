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
    int guardCastle(vector<string>& grid) {
        int n = grid[0].size();
        string& g1 = grid[0], & g2 = grid[1];
        int cr = 0, sr = 0;
        for (int i = 0; i < n; ++i) {
            if (cr == INT_MAX && sr == INT_MAX) return -1;

            if (g1[i] == 'C' || g2[i] == 'C') {
                int now = 0;
                if (g2[i] == 'C') now = 1;
                int other = 1 - now;
                if (grid[other][i] == 'S' || (i > 0 && grid[now][i - 1] == 'S') || (i + 1 < n && grid[now][i + 1] == 'S')) return -1;
                if (grid[other][i] == 'P' || (i > 0 && grid[now][i - 1] == 'P') || (i + 1 < n && grid[now][i + 1] == 'P')) {
                    cr = INT_MAX;
                    continue;
                }
                if (grid[other][i] == '.') ++cr;
                if (i > 0 && grid[now][i - 1] == '.') ++cr;
                if (i + 1 < n && grid[now][i + 1] == '.') ++cr;
                if (cr == 0) return 0;

                int left = INT_MAX;
                int j;
                for (j = i -1; j >= 0 && left > 0; --j) {
                    int r = 0;
                    if (g1[j] != '#' && g1[j + 1] != '#') ++r;
                    if (g2[j] != '#' && g2[j + 1] != '#') ++r;
                    left = min(left, r);
                    if (g1[j] == 'P' || g1[j] == 'S') break;
                    if (g2[j] == 'P' || g2[j] == 'S') break;
                }
                if (j < 0) left = 0;

                int right = INT_MAX;
                for (j = i + 1; j < n && right > 0; ++j) {
                    int r = 0;
                    if (g1[j] != '#' && g1[j - 1] != '#') ++r;
                    if (g2[j] != '#' && g2[j - 1] != '#') ++r;
                    right = min(right, r);
                    if (g1[j] == 'P' || g1[j] == 'S') break;
                    if (g2[j] == 'P' || g2[j] == 'S') break;
                }
                if (j == n) right = 0;
                cr = min(cr, left + right);
            } else if (g1[i] == 'S' || g2[i] == 'S') {
                if (sr == INT_MAX) continue;
                int r = 0;
                if (g1[i] == 'S' && g2[i] == 'S') {
                    if (i > 0 && (grid[0][i-1] == 'C' || grid[1][i - 1] == 'C')) return -1;
                    if (i + 1 < n && (grid[0][i + 1] == 'C' || grid[1][i + 1] == 'C')) return -1;
                    if (i > 0 && (grid[0][i - 1] == 'P' || grid[1][i - 1] == 'P')) {
                        sr = INT_MAX;
                        break;
                    }
                    if (i + 1 < n && (grid[0][i + 1] == 'P' || grid[1][i + 1] == 'P')) {
                        sr = INT_MAX;
                        break;
                    }
                    r = INT_MAX;
                } else {
                    int now = 0;
                    if (g2[i] == 'S') now = 1;
                    int other = 1 - now;
                    if (grid[other][i] == 'C' || (i > 0 && grid[now][i - 1] == 'C') || (i + 1 < n && grid[now][i + 1] == 'C')) return -1;
                    if (grid[other][i] == 'P' || (i > 0 && grid[now][i - 1] == 'P') || (i + 1 < n && grid[now][i + 1] == 'P')) {
                        sr = INT_MAX;
                        continue;
                    }

                    if (grid[other][i] == '.') ++r;
                    if (i > 0 && grid[now][i - 1] == '.') ++r;
                    if (i + 1 < n && grid[now][i + 1] == '.') ++r;
                }
                if (r == 0) break;

                int left = INT_MAX;
                int j;
                for (j = i - 1; j >= 0 && left > 0; --j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j + 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j + 1] != '#') ++xr;
                    left = min(left, xr);
                    if (g1[j] == 'P' || g1[j] == 'C') break;
                    if (g2[j] == 'P' || g2[j] == 'C') break;
                    if (g1[j] == 'S' || g2[j] == 'S') {
                        left = 0;
                        break;
                    }
                }
                if (j < 0) left = 0;

                int right = INT_MAX;
                for (j = i + 1; j < n && right > 0; ++j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j - 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j - 1] != '#') ++xr;
                    right = min(right, xr);
                    if (g1[j] == 'P' || g1[j] == 'C') break;
                    if (g2[j] == 'P' || g2[j] == 'C') break;
                    if (g1[j] == 'S' || g2[j] == 'S') {
                        right = 0;
                        break;
                    }
                }
                if (j == n) right = 0;
                r = min(r, left + right);
                sr += r;
            }
            //cout << i << ", " << cr << ", " << sr << endl;
        }
        if (cr == INT_MAX && sr == INT_MAX) return -1;
        return min(cr, sr);
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
    vector<string> grid = { "S.C.P#P.", ".....#.S" };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<string> grid = { "SP#P..P#PC#.S", "..#P..P####.#" };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = -1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<string> grid = { "#..#S....S.#....PP#...S.PC.P...S#...", "S.S.S.P#..##.S##..S#.#S...#.....P##S" };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}
}

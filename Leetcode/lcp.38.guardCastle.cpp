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
#include <cassert>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int guardCastle(vector<string>& grid) {
        int cr = getResult(grid, 'C', 'S', 'P');
        int sr = getResult(grid, 'S', 'C', 'P');
        if (cr == INT_MAX && sr == INT_MAX) return -1;
        return min(cr, sr);
    }

    int getResult(const vector<string>& gd, char x, char y, char z) {
        vector<string> grid = gd;
        for (auto& c : grid[0]) if (c == z) c = y;
        for (auto& c : grid[1]) if (c == z) c = y;

        int n = grid[0].size();
        const string& g1 = grid[0], & g2 = grid[1];
        int result = 0, r = 0;
        int now = 0, other = 0;
        bool xflag = true, nflag = true, sa2 = true;;
        for (int i = 0; i < n; ++i) {
            if (g1[i] == x || g2[i] == x) {
                nflag = true;
                if (g1[i] == y || g2[i] == y) return INT_MAX;
                if (g1[i] == g2[i]) {
                    if (i >= 1 && (g1[i - 1] == y || g2[i - 1] == y)) return INT_MAX;
                } else {
                    now = 0;
                    if (g2[i] == x) now = 1;
                    other = 1 - now;
                    if (i >= 1 && grid[now][i - 1] == y) return INT_MAX;
                }
            } else if (g1[i] == y || g2[i] == y) {
                nflag = false;
                if (g1[i] == g2[i]) {
                    if (i >= 1 && (g1[i - 1] == x || g2[i - 1] == x)) return INT_MAX;
                } else {
                    now = 0;
                    if (g2[i] == y) now = 1;
                    other = 1 - now;
                    if (i >= 1 && grid[now][i - 1] == x) return INT_MAX;
                }
            } else {
                if (r == 0) continue;
                int rr = 0;
                if (g1[i] != '#' && g1[i - 1] != '#') ++rr;
                if (g2[i] != '#' && g2[i - 1] != '#') ++rr;
                r = min(r, rr);
                continue;
            }

            sa2 = g1[i] == g2[i];
            if (r == 0 || xflag == nflag) {
                //r = 2;
            } else if (r == 1) {
                if (sa2) {
                    result += r;
                } else {
                    if (grid[other][i] == '#' && grid[now][i-1] == '#') {
                        //do nothing                        
                    } else if (grid[other][i] != '#' && grid[now][i - 1] != '#') {
                        result += 1;
                    } else if (grid[other][i] != '#' && grid[now][i - 1] == '#') {
                        result += 1;
                        grid[other][i] = '#';
                    } else {
                        result += 1;
                    }
                }
            } else if (r == 2) {
                if (sa2) {
                    result += r;
                } else {
                    if (grid[other][i] == '#' && grid[now][i - 1] == '#') {
                        //do nothing                        
                    } else if (grid[other][i] != '#' && grid[now][i - 1] != '#') {
                        result += 2;
                        grid[other][i] = '#';
                    } else if (grid[other][i] != '#' && grid[now][i - 1] == '#') {
                        result += 1;
                        grid[other][i] = '#';
                    } else {
                        result += 1;
                    }
                }
            } else {
                assert(false);
            }
            r = 2;
            xflag = nflag;

        }
        return result;
    }
};

class Solution2Error {
public:
    int guardCastle(vector<string>& grid) {
        int cr = getResult(grid, 'C', 'S', 'P');
        int sr = getResult(grid, 'S', 'C', 'P');
        if (cr == INT_MAX && sr == INT_MAX) return -1;
        return min(cr, sr);
    }

    int getResult(const vector<string>& grid, char x, char y, char z) {
        int n = grid[0].size();
        const string& g1 = grid[0], & g2 = grid[1];
        int r1 = 0, r2 = 0;

        int flag = 0;
        int lastindex = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int left = 0, right = 0, lr = INT_MAX;
            if (g1[i] == x || g2[i] == x) {
                int nflag = 1, now = 0, other = 0;
                if (g1[i] == x && g2[i] == x) {
                    if (i > 0 && (grid[0][i - 1] == y || grid[1][i - 1] == y)) return INT_MAX;
                    if (i > 0 && (grid[0][i - 1] == z || grid[1][i - 1] == z)) return INT_MAX;
                    if (i + 1 < n && (grid[0][i + 1] == y || grid[1][i + 1] == y)) return INT_MAX;
                    if (i + 1 < n && (grid[0][i + 1] == z || grid[1][i + 1] == z)) return INT_MAX;
                } else {
                    now = 0;
                    if (g2[i] == x) now = 1;
                    other = 1 - now;
                    if (grid[other][i] == y || grid[other][i] == z) return INT_MAX;
                    if (i > 0 && (grid[now][i - 1] == y || grid[now][i - 1] == z)) return INT_MAX;
                    if (i + 1 < n && (grid[now][i + 1] == y || grid[now][i + 1] == z)) return INT_MAX;
                    lr = 0;
                    if (grid[other][i] == '.') ++lr;
                    if (i > 0 && grid[now][i - 1] == '.') ++lr;
                    if (i + 1 < n && grid[now][i + 1] == '.') ++lr;
                }
                left = INT_MAX;
                int j;
                for (j = i - 1; j >= 0 && left > 0; --j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j + 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j + 1] != '#') ++xr;
                    left = min(left, xr);
                    if (g1[j] == y || g1[j] == z) break;
                    if (g2[j] == y || g2[j] == z) break;
                    if (g1[j] == x || g2[j] == x) {
                        left = 0;
                        break;
                    }
                }
                if (j < 0) left = 0;

                right = INT_MAX;
                for (j = i + 1; j < n && right > 0; ++j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j - 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j - 1] != '#') ++xr;
                    right = min(right, xr);
                    if (g1[j] == y || g1[j] == z) break;
                    if (g2[j] == y || g2[j] == z) break;
                    if (g1[j] == x || g2[j] == x) {
                        right = 0;
                        break;
                    }
                }
                if (j == n) right = 0;
                lr = min(lr, left + right);

                if (nflag == flag) {
                    r2 = right + r1;
                } else {
                    int nr1 = min(r2, r1 + left);
                    int nr2 = min(r2 + right, r1 + lr);
                    if (lastindex + 1 == i) {
                        nr1 = r1 + ((grid[now][i-1] == '.') ? 1 : 0);
                        nr2 = r2 + ((i + 1 < n && grid[other][i] == '.') ? 1 : 0);
                    }
                    r1 = nr1, r2 = nr2;
                }
                flag = nflag;
                lastindex = i;
            } else if (g1[i] == y || g1[i] == z || g2[i] == y || g2[i] == z) {
                int nflag = 2, now = 0, other = 0;
                if ((g1[i] == y || g1[i] == z) && (g2[i] == y || g2[i] == z)) {
                    if (i > 0 && (grid[0][i - 1] == x || grid[1][i - 1] == x)) return INT_MAX;
                    if (i + 1 < n && (grid[0][i + 1] == x || grid[1][i + 1] == x)) return INT_MAX;
                } else {
                    now = 0;
                    if (g2[i] == y || g2[i] == z) now = 1;
                    other = 1 - now;
                    if (i > 0 && grid[now][i - 1] == x) return INT_MAX;
                    if (i + 1 < n && grid[now][i + 1] == x) return INT_MAX;
                    lr = 0;
                    if (grid[other][i] == '.') ++lr;
                    if (i > 0 && grid[now][i - 1] == '.') ++lr;
                    if (i + 1 < n && grid[now][i + 1] == '.') ++lr;
                }
                left = INT_MAX;
                int j;
                for (j = i - 1; j >= 0 && left > 0; --j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j + 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j + 1] != '#') ++xr;
                    left = min(left, xr);
                    if (g1[j] == x) break;
                    if (g2[j] == x) break;
                    if (g1[j] == y || g2[j] == y || g1[j] == z || g2[j] == z) {
                        left = 0;
                        break;
                    }
                }
                if (j < 0) left = 0;

                right = INT_MAX;
                for (j = i + 1; j < n && right > 0; ++j) {
                    int xr = 0;
                    if (g1[j] != '#' && g1[j - 1] != '#') ++xr;
                    if (g2[j] != '#' && g2[j - 1] != '#') ++xr;
                    right = min(right, xr);
                    if (g1[j] == x) break;
                    if (g2[j] == x) break;
                    if (g1[j] == y || g2[j] == y || g1[j] == z || g2[j] == z) {
                        right = 0;
                        break;
                    }
                }
                if (j == n) right = 0;
                lr = min(lr, left + right);

                if (nflag == flag) {
                    r2 = right + r1;
                } else {
                    int nr1 = min(r2, r1 + left);
                    int nr2 = min(r2 + right, r1 + lr);
                    if (lastindex + 1 == i) {
                        nr1 = r1 + ((grid[now][i-1] == '.') ? 1 : 0);
                        nr2 = r2 + ((i + 1 < n && grid[other][i] == '.') ? 1 : 0);
                    }
                    r1 = nr1, r2 = nr2;
                }
                flag = nflag;
                lastindex = i;
            }
        }
        return r1;
    }
};
class Solution1Error {
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
TEST_F(TestSolution, Test3)
{
    vector<string> grid = { "..PP#.PC", "S#..S#.." };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<string> grid = { "C#.S.P...P", "P##...S..P" };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test5)
{
    vector<string> grid = { "S...S", "##C##" };
    Solution s;
    auto actual = s.guardCastle(grid);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}

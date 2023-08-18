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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> results(n, vector<int>(k));
        vector<vector<int>> nexts(n, vector<int>(k));
        int x = 0;
        for (int j = 0; j < n; ++j) {
            x += grid[0][j];
            x %= k;
            results[j][x] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int kk = 0; kk < k; ++kk) {
                nexts[0][(kk + grid[i][0]) % k] = results[0][kk];
            }
            for (int j = 1; j < n; ++j) {
                for (int kk = 0; kk < k; ++kk) {
                    int r = results[j][kk] + nexts[j - 1][kk];
                    if (r >= MOD) r -= MOD;
                    nexts[j][(kk + grid[i][j]) % k] = r;
                }
            }

            results.swap(nexts);
        }
        return results.back().front();
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
    vector<vector<int>> grid = { {5,2,4}, {3,0,5}, {0,7,2} };
    Solution s;
    auto actual = s.numberOfPaths(grid, 3);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}


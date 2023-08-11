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
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) return grid[0][0];
        vector<int> results = grid[0];
        for (int i = 1; i < n; ++i) {
            int mr1 = min(results[0], results[1]);
            int mr2 = max(results[0], results[1]);
            for (int j = 2; j < n; ++j) {
                if (results[j] < mr1) {
                    mr2 = mr1;
                    mr1 = results[j];
                } else if (results[j] < mr2) {
                    mr2 = results[j];
                }
            }
            cout << mr1 << ", " << mr2 << endl;
            vector<int> nexts(n);
            for (int j = 0; j < n; ++j) {
                if (results[j] == mr1) {
                    nexts[j] = grid[i][j] + mr2;
                } else {
                    nexts[j] = grid[i][j] + mr1;
                }
            }
            results = std::move(nexts);
            cout << "results: ";
            for (auto r : results) cout << r << " ";
            cout << endl;
        }

        return *min_element(results.begin(), results.end());
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
    vector<vector<int>> grid = { {-73,61,43,-48,-36}, {3,30,27,57,10}, {96,-76,84,59,-15}, {5,-49,76,31,-7}, {97,91,61,-46,67} };
    Solution s;
    auto actual = s.minFallingPathSum(grid);
    decltype(actual) expect = -192;
    EXPECT_EQ(expect, actual);
}
}

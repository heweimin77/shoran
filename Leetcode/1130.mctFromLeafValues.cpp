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
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<pair<int, int>>> results(n, vector < pair<int, int>>(n));
        for (int i = 0; i < n; ++i) {
            results[i][i] = { 0, arr[i] };
        }
        for (int d = 1; d < n; ++d) {
            for (int i = 0, j = d; j < n; ++i, ++j) {
                int r = INT_MAX;
                for (int k = i; k < j; ++k) {
                    r = min(r, results[i][k].first + results[k + 1][j].first + results[i][k].second * results[k + 1][j].second);
                }
                results[i][j] = { r, max(results[i][i].second, results[i + 1][j].second) };
            }
        }

        return results[0][n - 1].first;
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
    vector<int> arr = { 6, 2, 4 };
    Solution s;
    auto actual = s.mctFromLeafValues(arr);
    decltype(actual) expect = 32;
    EXPECT_EQ(expect, actual);
}
}

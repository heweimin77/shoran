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
    int mergeStones(vector<int> &stones, int k)
    {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) return -1;
        vector<int> sums(n);
        int s = 0;
        for (int i = 0; i < n; ++i) {
            sums[i] = s += stones[i];
        }
        vector<vector<vector<int>>> results(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        for (int i = 0; i < n; ++i) {
            results[i][i][1] = 0;
        }
        for (int d = 1; d < n; ++d) {
            for (int i = 0, j = i + d; j < n; ++i, ++j) {
                for (int kk = 2; kk <= k; ++kk) {
                    // 计算results[i][j][kk]
                    int r = INT_MAX;
                    for (int m = i; m < j; ++m) {
                        if (results[i][m][1] == -1 || results[m + 1][j][kk - 1] == -1) continue;
                        r = min(r, results[i][m][1] + results[m + 1][j][kk - 1]);
                    }
                    if (r != INT_MAX) {
                        results[i][j][kk] = r;
                    }
                }
                if (results[i][j][k] != -1) {
                    auto s = sums[j];
                    if (i > 0) s -= sums[i - 1];
                    results[i][j][1] = results[i][j][k] + s;
                }
            }
        }
        return results[0][n - 1][1];
    }
};

class TestSolution :public testing::Test {
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
    vector<int> stones = { 3,2,4,1 };
    Solution s;
    auto actual = s.mergeStones(stones, 2);
    decltype(actual) expect = 20;
    EXPECT_EQ(expect, actual);
}

}


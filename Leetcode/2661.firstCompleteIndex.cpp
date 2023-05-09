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
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        vector<pair<int, int>> indexes(arr.size());
        int m = mat.size(), n = mat[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                indexes[mat[i][j] - 1] = { i, j };
            }
        }
        vector<int> rsum(m), csum(n);
        for (int i = 0; i < arr.size(); ++i) {
            auto& p = indexes[arr[i] - 1];
            if (++rsum[p.first] == n) {
                return i;
            }
            if (++csum[p.second] == m) {
                return i;
            }
        }
        return 0;
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
    vector<int> arr = { 1,3,4,2 };
    vector<vector<int>> mat = { {1, 4},{2, 3 }};
    Solution s;
    auto actual = s.firstCompleteIndex(arr, mat);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}


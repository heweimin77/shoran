#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int n = (matrix[0].size() + 63) / 64;
        map<vector<unsigned long long>, int> counts;
        for (auto& row : matrix) {
            vector<unsigned long long> flag(n);
            bool invert = row[0] == 1;
            for (int i = 0; i < row.size(); ++i) {
                if (invert) {
                    flag[i >> 6] |= (1 - row[i]) << (i & 0x3F);
                } else {
                    flag[i >> 6] |= row[i] << (i & 0x3F);
                }
            }
            ++counts[flag];
        }
        int result = 0;
        for (auto& r : counts) {
            result = max(result, r.second);
        }
        return result;
    }
};

class Solution2Map {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        map<vector<int>, int> counts;
        for (auto& row : matrix) {
            if (row[0] == 1) {
                for (auto& x : row) {
                    x = 1 - x;
                }
            }
            ++counts[row];
        }
        int result = 0;
        for (auto& r : counts) {
            result = max(result, r.second);
        }
        return result;
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
    vector<vector<int>> matrix = {{0, 1}, {1, 1}};
    Solution s;
    auto actual = s.maxEqualRowsAfterFlips(matrix);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}


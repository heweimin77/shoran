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
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> results(n);
        for (int i = 0; i < n; ++i) {
            int result = INT_MAX;
            int r = k;
            unordered_map<int, int> counts;
            for (int j = i; j >= 0; --j) {
                int cnt = ++counts[nums[j]];
                if (cnt == 2) r += 2;
                else if(cnt > 2) ++r;
                if (j > 0) {
                    result = min(result, results[j - 1] + r);
                } else {
                    result = min(result, r);
                }
            }
            results[i] = result;
        }

        return results.back();
    }
};

class Solution2Timeout {
public:
    int minCost(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> results(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            unordered_map<int, int> counts;
            int result = k;
            for (int j = i; j < n; ++j) {
                auto cnt = ++counts[nums[j]];
                if (cnt == 2) {
                    result += 2;
                } else if (cnt > 2) {
                    ++result;
                }
                results[i][j] = result;
            }
        }

        for (int d = 2; d < n; ++d) {
            for (int i = 0, j = d; j < n; ++i, ++j) {
                int result = results[i][j];
                for (int k = i; k < j; ++k) {
                    result = min(result, results[i][k] + results[k+1][j]);
                }
                results[i][j] = result;
            }
        }
        return results[0][n-1];
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
    vector<int> nums = { 1,2,1,2,1,3,3 };
    Solution s;
    auto actual = s.minCost(nums, 2);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}
}

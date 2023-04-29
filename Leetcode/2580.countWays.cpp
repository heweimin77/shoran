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
    int countWays(vector<vector<int>> &ranges)
    {
        sort(ranges.begin(), ranges.end());
        int right = INT_MIN;
        int r = 0;
        for (auto &range : ranges) {
            if (range[0] > right) {
                ++r;
                right = range[1];
            } else {
                right = max(right, range[1]);
            }
        }
        return fast_power(2, r, 1e9 + 7);
    }
    long long fast_power(long long base, long long n, long long module)
    {
        long long result = 1;
        int mask = 1;
        for (int mask = 1; mask <= n; mask <<= 1) {
            if (mask & n) {
                result *= base;
                result %= module;
            }
            base *= base;
            base %= module;
        }
        return result;
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
    vector<vector<int>> ranges = { {6,10},{5,15 } };
    Solution s;
    auto actual = s.countWays(ranges);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}


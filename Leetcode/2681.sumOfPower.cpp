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
    static constexpr int MOD = 1e9 + 7;
public:
    int sumOfPower(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        long long lowsum = 0;
        long long result = 0;
        for (auto n : nums) {
            long long r = lowsum + n;
            r *= n;
            r %= MOD;
            r *= n;
            result += r;
            result %= MOD;
            lowsum <<= 1;
            lowsum += n;
            lowsum %= MOD;
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
    vector<int> nums = { 2, 1, 4 };
    Solution s;
    auto actual = s.sumOfPower(nums);
    decltype(actual) expect = 141;
    EXPECT_EQ(expect, actual);
}

}

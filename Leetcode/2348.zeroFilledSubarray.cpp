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
    long long zeroFilledSubarray(vector<int> &nums)
    {
        int n = nums.size();
        int i = n;
        int j = 0;
        long long result = 0;
        while (i != j) {
            for (i = j; i < n && nums[i] != 0; ++i);
            for (j = i; j < n && nums[j] == 0; ++j);
            long long d = j - i;
            result += d * (d + 1) / 2;
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
    vector<int> nums = { 1,3,0,0,2,0,0,4 };
    Solution s;
    auto actual = s.zeroFilledSubarray(nums);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}

}


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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int longestNiceSubarray(vector<int> &nums)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int j = i;
            int flag = 0;
            for (; j < nums.size(); ++j) {
                if (flag & nums[j]) break;
                flag |= nums[j];
            }
            result = max(result, j - i);
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
    vector<int> nums = { 1,3,8,48,10 };
    Solution s;
    auto actual = s.longestNiceSubarray(nums);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

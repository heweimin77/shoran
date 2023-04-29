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
    bool validPartition(vector<int> &nums)
    {
        if (nums.size() == 2) return nums[0] == nums[1];
        unsigned mask = 1;
        if (nums[0] == nums[1]) mask |= 0x4;
        for (size_t i = 2; i < nums.size(); ++i) {
            if (mask == 0) return false;
            if ((nums[i] == nums[i - 1] && (mask & 0x2)) ||
                ((nums[i] == nums[i - 1] && nums[i] == nums[i - 2] && (mask & 0x1))) ||
                ((nums[i] == nums[i - 1] + 1 && nums[i] == nums[i - 2] + 2 && (mask & 0x1)))) {
                mask |= 0x8;
            }
            mask >>= 1;
        }
        return mask & 0x4;
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
    vector<int> nums = { 803201,803201,803201,803201,803202,803203 };
    Solution s;
    auto actual = s.validPartition(nums);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}

}


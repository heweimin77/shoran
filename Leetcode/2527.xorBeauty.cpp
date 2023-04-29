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
    int xorBeauty(vector<int> &nums)
    {
        int n = nums.size();
        unsigned flag = 0;
        if (n & 1) flag = ~flag;
        unsigned xorsum = 0;
        for (auto x : nums) {
            xorsum ^= x;
        }
        unsigned orsum = 0;
        for (auto x : nums) {
            unsigned r = (x & flag) | ((~x) & xorsum);
            orsum ^= r;
        }
        unsigned result = 0;
        for (auto x : nums) {
            unsigned r = (x & orsum);
            result ^= r;
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
    vector<int> nums = { 1,4 };
    Solution s;
    auto actual = s.xorBeauty(nums);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}

}


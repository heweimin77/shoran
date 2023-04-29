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
    int maximumSum(vector<int> &nums)
    {
        int maxnums[82] = { 0 };
        int result = -1;
        for (auto n : nums) {
            int x = 0;
            for (int i = n; i > 0; i /= 10) x += i % 10;
            if (maxnums[x] > 0) {
                result = max(result, maxnums[x] + n);
            }
            maxnums[x] = max(maxnums[x], n);
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
    vector<int> nums = { 18,43,36,13,7 };
    Solution s;
    auto actual = s.maximumSum(nums);
    decltype(actual) expect = 54;
    EXPECT_EQ(expect, actual);
}

}


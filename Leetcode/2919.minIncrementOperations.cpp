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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long minIncrementOperations(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> results(n);
        results[0] = nums[0] >= k ? 0 : k - nums[0];
        results[1] = nums[1] >= k ? 0 : k - nums[1];
        results[2] = nums[2] >= k ? 0 : k - nums[2];
        for (int i = 3; i < n; ++i) {
            long long r = nums[i] >= k ? 0 : k - nums[i];
            r += min(min(results[i - 1], results[i - 2]), results[i - 3]);
            results[i] = r;
        }
        return min(min(results[n - 1], results[n - 2]), results[n - 3]);
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
    vector<int> nums = { 2,3,0,0,2 };
    Solution s;
    auto actual = s.minIncrementOperations(nums, 4);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

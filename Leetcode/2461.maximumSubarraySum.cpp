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
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        unordered_map<int,int> counts;
        int ncount = 0;
        long long result = 0;
        long long sum = 0;
        for (int i = 0; i < k - 1; ++i) {
            if (++counts[nums[i]] == 1) ++ncount;
            sum += nums[i];
        }
        for (int i = k - 1; i < nums.size(); ++i) {
            if (++counts[nums[i]] == 1) ++ncount;
            sum += nums[i];
            if (ncount == k) result = max(result, sum);
            sum -= nums[i - k + 1];
            if (--counts[nums[i - k + 1]] == 0) --ncount;
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
    vector<int> nums = { 1,5,4,2,9,9,9 };
    Solution s;
    auto actual = s.maximumSubarraySum(nums, 3);
    decltype(actual) expect = 15;
    EXPECT_EQ(expect, actual);
    
}

}

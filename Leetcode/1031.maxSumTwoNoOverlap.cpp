#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int maxSumTwoNoOverlap(vector<int> &nums, int firstLen, int secondLen)
    {
        int n = nums.size();
        vector<int> lsums(n), rsums(n);
        auto s = lsums[firstLen - 1] = accumulate(nums.begin(), nums.begin() + firstLen, 0);
        for (int i = firstLen; i < n; ++i) {
            s += nums[i] - nums[i - firstLen];
            lsums[i] = max(lsums[i - 1], s);
        }
        s = rsums[n - firstLen] = accumulate(nums.end() - firstLen, nums.end(), 0);
        for (int i = n - firstLen - 1; i >= 0; --i) {
            s += nums[i] - nums[i + firstLen];
            rsums[i] = max(rsums[i + 1], s);
        }

        s = accumulate(nums.begin(), nums.begin() + secondLen, 0);
        int result = s + rsums[secondLen];
        for (int i = 0, j = secondLen; j < n; ++i, ++j) {
            s += nums[j] - nums[i];
            if (i >= firstLen - 1) {
                result = max(result, s + lsums[i]);
            }
            if (j + 1 <= n - firstLen) {
                result = max(result, s + rsums[j + 1]);
            }
            
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
    vector<int> nums = { 0,6,5,2,2,5,1,9,4 };
    Solution s;
    auto actual = s.maxSumTwoNoOverlap(nums, 1, 2);
    decltype(actual) expect = 20;
    EXPECT_EQ(expect, actual);
}

}

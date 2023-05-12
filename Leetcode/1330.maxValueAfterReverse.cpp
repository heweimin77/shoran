#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        for (int i = 1; i < n; ++i) result += abs(nums[i] - nums[i - 1]);
        if (nums.size() <= 2) return result;
        int delta = 0;
        for (int j = 1; j < n - 1; ++j) {
            delta = max(delta, abs(nums[0] - nums[j + 1]) - abs(nums[j] - nums[j + 1]));
        }
        for (int i = 1; i < n - 1; ++i) {
            delta = max(delta, abs(nums[n-1] - nums[i-1]) - abs(nums[i] - nums[i - 1]));
        }
        int minmax = INT_MIN, maxmin = INT_MAX;
        for (int i = 1; i < nums.size(); ++i) {
            int min1 = min(nums[i], nums[i - 1]), max1 = max(nums[i], nums[i - 1]);
            minmax = max(minmax, min1);
            maxmin = min(maxmin, max1);
        }
        delta = max(delta, 2 * (minmax - maxmin));
        return result + delta;
    }
};

class Solution2Timeout12 {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) result += abs(nums[i] - nums[i - 1]);
        int r = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                int d = 0;
                if (i > 0) {
                    d += abs(nums[j] - nums[i - 1]) - abs(nums[i] - nums[i - 1]);
                }
                if (j + 1 < nums.size()) {
                    d += abs(nums[i] - nums[j + 1]) - abs(nums[j] - nums[j + 1]);
                }
                r = max(r, d);
            }
        }
        return result + r;
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
    vector<int> nums = { 2,3,1,5,4 };
    Solution s;
    auto actual = s.maxValueAfterReverse(nums);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
}


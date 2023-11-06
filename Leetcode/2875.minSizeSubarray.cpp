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
    int minSizeSubarray(vector<int>& nums, int target) {
        long long sum = accumulate(nums.begin(), nums.end(), 0LL);
        int result = 0;
        if (target >= sum) {
            result += target / sum * nums.size();
            target %= sum;
        }
        if (target == 0) return result;

        vector<long long> data;
        int s = 0;
        for (auto n : nums) {
            s += n;
            data.push_back(s);
        }
        int r = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = lower_bound(data.begin(), data.end(), target);
            if (it != data.end() && *it == target) {
                r = min(r, (int)(it - data.begin()) - i + 1);
            }
            target += nums[i];
            data.push_back(data.back() + nums[i]);
        }
        return r == INT_MAX ? -1 : result + r;
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
    vector<int> nums = { 1,2,3 };
    Solution s;
    auto actual = s.minSizeSubarray(nums, 5);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}

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
    long long countGood(vector<int> &nums, int k)
    {
        unordered_map<int, int> counts;
        int n = nums.size();
        int j = 0;
        int kk = 0;
        long long result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (; j < n && kk < k; ++j) {
                int x = ++counts[nums[j]];
                kk += x - 1;
            }
            if (kk < k) break;
            result += n - j + 1;
            int x = --counts[nums[i]];
            kk -= x;
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
    vector<int> nums = { 1,1,1,1,1 };
    Solution s;
    auto actual = s.countGood(nums, 10);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

}


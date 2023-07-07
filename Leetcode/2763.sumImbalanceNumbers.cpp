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

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int sumImbalanceNumbers(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int r = 0;
            multiset<int> data;
            data.insert(nums[i]);
            for (int j = i + 1; j < nums.size(); ++j) {
                int n = nums[j];
                auto it = data.insert(n);
                auto jt = it;
                ++jt;
                if (jt != data.end() && *jt - *it > 1) ++r;
                if (it != data.begin()) {
                    auto kt = it;
                    --kt;
                    if (jt != data.end() && *jt - *kt > 1) --r;
                    if (n - *kt > 1) ++r;
                }
                //cout << i << ", " << j << ": " << r << endl;
                result += r;
            }
        }
        return result;
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

TEST_F(TestSolution, Test1)
{
    vector<int> nums = { 2,3,1,4 };
    Solution s;
    auto actual = s.sumImbalanceNumbers(nums);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 1,3,3,3,5 };
    Solution s;
    auto actual = s.sumImbalanceNumbers(nums);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}
}

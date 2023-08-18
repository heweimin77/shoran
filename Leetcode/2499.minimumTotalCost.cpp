#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        vector<int> indexes;
        int x = 0;
        int cnt = 0;
        int n = nums1.size();
        for (int i = 0; i < n; ++i) {
            if (nums1[i] != nums2[i]) continue;
            indexes.push_back(i);
            if (x == nums1[i]) {
                ++cnt;
            } else {
                if (--cnt < 0) {
                    x = nums1[i];
                    cnt = 1;
                }
            }
        }
        cnt = count_if(indexes.begin(), indexes.end(), [&](int i) {
            return nums1[i] == x;
            });

        long long result = accumulate(indexes.begin(), indexes.end(), 0LL);
        if (cnt + cnt <= indexes.size()) return result;
        cnt -= indexes.size() - cnt;
        for (int i = 0; i < n && cnt > 0; ++i) {
            if (nums1[i] != nums2[i] && nums1[i] != x && nums2[i] != x) {
                result += i;
                --cnt;
            }
        }
        return cnt > 0 ? -1 : result;
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
    vector<int> nums1 = { 1,2,3,4,5 };
    vector<int> nums2 = { 1,2,3,4,5 };
    Solution s;
    auto actual = s.minimumTotalCost(nums1, nums2);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums1 = { 1,2,2 };
    vector<int> nums2 = { 1,2,2 };
    Solution s;
    auto actual = s.minimumTotalCost(nums1, nums2);
    decltype(actual) expect = -1;
    EXPECT_EQ(expect, actual);
}
}


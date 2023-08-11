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
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        int s1 = accumulate(nums1.begin(), nums1.end(), 0);
        if (s1 <= x) return 0;
        int s2 = accumulate(nums2.begin(), nums2.end(), 0);

        int n = nums1.size();
        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&nums2](int lhs, int rhs) {
            return nums2[lhs] < nums2[rhs];
            });

        vector<int> results(n, s1);
        for (int i = 1; i <= n; ++i) {
            vector<int> nexts(n, 0);
            nexts[0] = s1 + s2 * i - (nums1[indexes[0]] + nums2[indexes[0]] * i);
            if (nexts[0] <= x) return i;
            for (int j = 1; j < n; ++j) {
                int r = results[j - 1] + s2 - (nums1[indexes[j]] + nums2[indexes[j]] * i);
                if (r <= x) return i;
                nexts[j] = min(nexts[j - 1], r);
            }
            results = std::move(nexts);
        }
        return -1;
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
    vector<int> nums1 = { 1,2,3 };
    vector<int> nums2 = { 1,2,3 };
    Solution s;
    auto actual = s.minimumTime(nums1, nums2, 4);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

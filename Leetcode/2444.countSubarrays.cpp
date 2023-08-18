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
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();
        long long result = 0;
        int i = 0, j = 0;
        while (i < n) {
            while (i < n && (nums[i] < minK || nums[i] > maxK)) ++i;
            if (i == n) break;
            j = i + 1;
            while (j < n && (nums[j] >= minK && nums[j] <= maxK)) ++j;
            result += countSubarraysImpl(nums, minK, maxK, i, j);
            i = j;
        }
        return result;
    }
    long long countSubarraysImpl(vector<int>& nums, int minK, int maxK, int i, int j) {
        long long count = j - i;
        if (minK == maxK) return (count + 1) * count / 2;

        long long minIndex = -1, maxIndex = -1;
        int start = i;
        long long result = 0;
        while (start < j && nums[start] != minK && nums[start] != maxK) ++start;

        while (start < j) {
            int finish = start + 1;
            while (finish < j && nums[finish] != minK && nums[finish] != maxK) ++finish;
            if (nums[start] == minK) {
                if (maxIndex >= 0) {
                    result += (maxIndex - i + 1) * (finish - start);
                }
                minIndex = start;
            } else {
                if (minIndex >= 0) {
                    result += (minIndex - i + 1) * (finish - start);
                }
                maxIndex = start;

            }
            start = finish;
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
    vector<int> nums = { 1,3,5,2,7,5 };
    Solution s;
    auto actual = s.countSubarrays(nums, 1, 5);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 1,2,9,9,2,9,1,9,2,9,1,2,2,2,2 };
    Solution s;
    auto actual = s.countSubarrays(nums, 1, 9);
    decltype(actual) expect = 81;
    EXPECT_EQ(expect, actual);
}
}


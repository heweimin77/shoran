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
    vector<long long> minOperations(vector<int> &nums, vector<int> &queries)
    {
        size_t n = nums.size();
        sort(nums.begin(), nums.end());
        vector<long long> sums(n);
        long long s = 0;
        for (size_t i = 0; i < n; ++i) {
            s += nums[i];
            sums[i] = s;
        }
        vector<long long> results(queries.size());
        for (size_t i = 0; i < queries.size(); ++i) {
            auto t = queries[i];
            auto it = lower_bound(nums.begin(), nums.end(), t);
            long long x = it - nums.begin();
            long long r = 0;
            if (x > 0) {
                r += t * x - sums[x - 1];
            }
            if (x < n) {

                r += sums[n - 1] - (n - x) * t;
                if (x > 0) {
                    r -= sums[x - 1];
                }
            }
            results[i] = r;
        }
        return results;
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
    vector<int> nums = { 3,1,6,8 };
    vector<int> queries = {1, 5};
    Solution s;
    auto actual = s.minOperations(nums, queries);
    decltype(actual) expect = {14, 10};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


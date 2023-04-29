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
    vector<int> goodIndices(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> left(n), right(n);
        calc(nums.begin(), nums.end(), left.begin());
        calc(nums.rbegin(), nums.rend(), right.rbegin());
        vector<int> results;
        for (int i = k; i + k < n; ++i) {
            if (left[i - 1] >= k && right[i + 1] >= k) results.push_back(i);
        }
        return results;
    }
    template<class Iterator>
    void calc(Iterator first, Iterator last, Iterator r)
    {
        *r = 1;
        for (++first, ++r; first != last; ++first, ++r) {
            if (*first <= *(first - 1)) {
                *r = *(r - 1) + 1;
            } else {
                *r = 1;
            }
        }
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
    vector<int> nums = { 253747,459932,263592,354832,60715,408350,959296 };
    Solution s;
    auto actual = s.goodIndices(nums, 2);
    decltype(actual) expect = {3};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

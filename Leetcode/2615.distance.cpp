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
    vector<long long> distance(vector<int> &nums)
    {
        unordered_map<int, vector<int>> value2indexes;
        for (int i = 0; i < nums.size(); ++i) {
            value2indexes[nums[i]].push_back(i);
        }
        vector<long long> results(nums.size());
        for (auto &r : value2indexes) {
            if (r.second.size() == 1) continue;
            long long n = r.second.size();
            long long rsum = accumulate(r.second.begin(), r.second.end(), 0LL);
            long long lsum = 0;
            for (auto i : r.second) {
                results[i] = rsum - lsum - n * i;
                rsum -= i;
                lsum += i;
                n -= 2;
            }
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
    vector<int> nums = { 1,3,1,1,2 };
    Solution s;
    auto actual = s.distance(nums);
    decltype(actual) expect = { 5,0,3,4,0 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


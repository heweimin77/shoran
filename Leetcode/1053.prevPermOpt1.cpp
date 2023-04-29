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
    vector<int> prevPermOpt1(vector<int> &arr)
    {
        for (int i = arr.size() - 2; i >= 0; --i) {
            if (arr[i] > arr[i + 1]) {
                auto it = lower_bound(arr.begin() + i + 1, arr.end(), arr[i]);
                it = lower_bound(arr.begin() + i + 1, it, *(it - 1));
                swap(arr[i], *it);
                break;
            }
        }
        return arr;
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
    vector<int> nums = { 3,1,1,3 };
    Solution s;
    auto actual = s.prevPermOpt1(nums);
    decltype(actual) expect = { 1,3,1,3 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


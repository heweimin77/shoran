﻿#include <string>
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
    int trafficCommand(vector<string>& directions) {
        return 0;
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
    vector<string> directions = { "W","N","ES","W" };
    Solution s;
    auto actual = s.trafficCommand(directions);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

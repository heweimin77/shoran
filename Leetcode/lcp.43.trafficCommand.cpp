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
#define MAKE_STATE(e, s, w, n)  ((e) | ((s) << 8) | ((w) << 16) | ((n) << 24))
#define GET_EAST(state)  ((state) & 0xFF)
#define GET_SOUTH(state) (((state) >> 8) & 0xFF)
#define GET_WEST(state) (((state) >> 8) & 0xFF)
#define GET_NORTH(state) (((state) >> 8) & 0xFF)

public:
    int trafficCommand(vector<string> &directions)
    {
        
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

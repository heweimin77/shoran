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
    int longestIdealString(string s, int k)
    {
        int results[26] = { 0 };
        for (auto c : s) {
            int i = c - 'a';
            auto left = max(0, i - k);
            auto right = min(26, i + k + 1);
            results[i] = *max_element(results + left, results + right) + 1;
        }
        return *max_element(results, results + 26);
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
    Solution s;
    auto actual = s.longestIdealString("acfgbd", 2);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}

}


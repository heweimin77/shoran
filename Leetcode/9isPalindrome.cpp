#include <string>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

namespace {

class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        for (size_t i = 0, j = s.size()-1; i < j; ++i, --j) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
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

    Solution s;
    auto actual = s.isPalindrome(121);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{

    Solution s;
    auto actual = s.isPalindrome(-121);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{

    Solution s;
    auto actual = s.isPalindrome(10);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}
}



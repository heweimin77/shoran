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

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minimumScore(string s, string t) {
        int n = t.size();
        vector<int> left(n, INT_MAX), right(n, INT_MIN);
        int i = 0;
        int lastj = -1;
        for (int j = 0; j < n; ++j) {
            while (i < s.size() && s[i] != t[j]) ++i;
            if (i == s.size()) break;
            left[j] = i++;
            lastj = j;
        }
        if (lastj == n - 1) return 0;
        int result = n - lastj - 1;

        i = s.size() - 1;
        lastj = n;
        for (int j = n - 1; j >= 0; --j) {
            while (i >= 0 && s[i] != t[j]) --i;
            if (i < 0) break;
            right[j] = i--;
            lastj = j;
        }
        if (lastj == 0) return 0;

        i = 0;
        for (int j = lastj; j < n; ++j) {
            while (left[i] < right[j]) ++i;
            result = min(result, j - i);
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
    Solution s;
    auto actual = s.minimumScore("abacaba", "bzaa");
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    Solution s;
    auto actual = s.minimumScore("cde", "xyz");
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    Solution s;
    auto actual = s.minimumScore("eeecaeecdeeadcdbcaa", "edecabe");
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.minimumScore("acdedcdbabecdbebda", "bbecddb");
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

}

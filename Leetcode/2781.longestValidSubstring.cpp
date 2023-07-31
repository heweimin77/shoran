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
    int longestValidSubstring(string word, vector<string>& forbidden) {
        unordered_set<string> dicts;
        for (auto& w : forbidden) {
            dicts.insert(w);
        }

        int result = 0;
        int n = word.size();
        int j = n;
        for (int i = n - 1; i >= 0; --i) {
            string s;
            for (int k = 1; k <= 10 && i + k <= j; ++k) {
                s += word[i + k - 1];
                if (dicts.count(s) > 0) {
                    j = i + k - 1;
                    break;
                }
            }
            result = max(result, j - i);
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
    vector<string> forbidden = { "aaa","cb" };
    Solution s;
    auto actual = s.longestValidSubstring("cbaaaabc", forbidden);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<string> forbidden = { "de","le","e" };
    Solution s;
    auto actual = s.longestValidSubstring("leetcode", forbidden);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
}

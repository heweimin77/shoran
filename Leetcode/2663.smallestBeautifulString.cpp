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
    string smallestBeautifulString(string s, int k) {
        char limit = 'a' + k;
        for (int i = s.size() - 1; i >= 0; --i) {
            for (++s[i]; s[i] < limit; ++s[i]) {
                if (i >= 1 && s[i] == s[i - 1]) continue;
                if (i >= 2 && s[i] == s[i - 2]) continue;
                for (int j = i + 1; j < s.size(); ++j) {
                    for (s[j] = 'a'; true; ++s[j]) {
                        if (s[j] == s[j - 1]) continue;
                        if (j >= 2 && s[j] == s[j - 2]) continue;
                        break;
                    }
                }
                return s;
            }
        }
        return "";
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
    Solution s;
    auto actual = s.smallestBeautifulString("abcz", 26);
    decltype(actual) expect = "abda";
    EXPECT_EQ(expect, actual);
}
}

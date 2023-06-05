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
    int maxRepOpt1(string text)
    {
        int counts[26] = { 0 };
        vector<pair<char, int>> paris;
        int count = 0;
        char c = text[0];
        for (auto ch : text) {
            ++counts[ch - 'a'];
            if (ch == c) {
                ++count;
            } else {
                paris.push_back({ c, count });
                c = ch;
                count = 1;
            }
        }
        paris.push_back({ c, count });
        int result = paris[0].second;
        if (paris[0].second != counts[paris[0].first - 'a']) {
            ++result;
        }
        if (paris.size() >= 2) {
            int r = paris[1].second;
            if (paris[1].second != counts[paris[1].first - 'a']) {
                ++r;
            }
            result = max(result, r);
        }
        for (int i = 2; i < paris.size(); ++i) {
            int r = paris[i].second;
            if (paris[i - 1].second == 1 && paris[i - 2].first == paris[i].first) {
                r += paris[i - 2].second;
            }
            if (r != counts[paris[i].first - 'a']) {
                ++r;
            }
            result = max(result, r);
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

TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.maxRepOpt1("abcdef");
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

}

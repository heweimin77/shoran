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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long sumScores(string s)
    {
        vector<int> lcp = getLcp(s);
        return accumulate(lcp.begin(), lcp.end(), (long long)s.size());
    }
    vector<int> getLcp(const string &s)
    {
        int n = s.size();
        vector<int> lcp(n);
        lcp[0] = 0;
        int left = 0, right = 0;
        for (int i = 1; i < n; ++i) {
            //0, right-left = left, right;  i, right ==   i - left ,right - left
            if (i <= right && i + lcp[i - left] <= right) {
                lcp[i] = lcp[i - left];
            } else {
                int r = max(0, right - i + 1);
                while (i + r < n && s[i + r] == s[r]) ++r;
                lcp[i] = r;
                left = i;
                right = i + lcp[i] - 1;
            }

        }
        return lcp;
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
    auto actual = s.sumScores("babab");
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}
}


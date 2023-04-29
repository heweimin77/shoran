#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    string lastSubstring(string s)
    {
        char mchar = *max_element(s.begin(), s.end());
        if (mchar == 'a') return s;
        int mfirst = s.find(mchar);
        int mlast = s.find(mchar, mfirst + 1);
        if (mlast == string::npos) return s.substr(mfirst);
        s.push_back('a'); // 1、保护最后count个，如果count与mcount相同，其实比当前的最大值小；2、保护find函数中i + 1不会超过s.size()；
        int mlen = mlast - mfirst;
        int mcount = 1;
        int first = mfirst;
        int count = 1;
        for (int i = mlast, j = 0; i < s.size(); i = j) {
            j = s.find(mchar, i + 1);
            if (j == string::npos) j = s.size();
            int cr = compare(s, i, j - i, mfirst, mlen);
            if (cr == 0) {
                ++count;
            } else if (cr > 0) {
                mfirst = first = i;
                mlen = j - i;
                count = mcount = 1;
            } else {
                if (count > mcount || (count == mcount &&
                    lexicographical_compare(s.begin() + mfirst + mlen * mcount, s.end(),
                        s.begin() + first + mlen * mcount, s.end()))) {
                    mfirst = first;
                    mcount = count;
                }
                first = j;
                count = 0;
            }
        }
        s.pop_back();
        return s.substr(mfirst);
    }
    int compare(const string &s, int first, int len, int mfirst, int mlen)
    {
        int ll = min(len, mlen);
        for (int i = first, j = mfirst; i < first + len; ++i, ++j) {
            if (s[i] != s[j]) {
                return s[i] - s[j];
            }
        }
        return mlen - len;
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
    vector<int> jump = {6};
    vector<int> cost = {10};
    Solution s;
    auto actual = s.lastSubstring("abab");
    decltype(actual) expect = "bab";
    EXPECT_EQ(expect, actual);
}

}

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
    vector<int> closestPrimes(int left, int right)
    {
        int sz = (right + 1) * sizeof(int);
        int *flag = (int *)malloc(sz);
        memset(flag, 0, sz);
        flag[0] = flag[1] = 1;
        for (int i = 2; i <= right; ++i) {
            if (flag[i]) continue;
            for (int j = i + i; j <= right; j += i) {
                flag[j] = 1;
            }
        }
        int ll = 0, rr = 0;
        for (ll = left; ll <= right && flag[ll]; ++ll);
        if (ll >= right) return { -1, -1 };
        int len = INT_MAX, rl = -1;
        for (rr = ll + 1; rr <= right; ++rr) {
            if (flag[rr]) continue;
            if (rr - ll < len) {
                len = rr - ll;
                rl = ll;
            }
            ll = rr;
        }
        if (len == INT_MAX) return { -1, -1 };
        return { rl, rl + len };

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
    auto actual = s.closestPrimes(10, 19);
    decltype(actual) expect = { 11, 13 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


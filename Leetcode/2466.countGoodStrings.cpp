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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one)
    {
        constexpr int MOD = 1e9 + 7;
        vector<int> results(high + 1);
        results[0] = 1;
        for (int i = min(one, zero); i <= high; ++i) {
            int r = 0;
            if (i >= one) {
                r += results[i - one];
            }
            if (i >= zero) {
                r += results[i - zero];
            }
            if (r >= MOD) r -= MOD;
            results[i] = r;
        }
        return accumulate(results.begin() + low, results.end(), 0LL) % MOD;
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
    auto actual = s.countGoodStrings(3, 3, 1, 1);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
    
}

}

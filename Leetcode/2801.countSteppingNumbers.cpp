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
    static constexpr int MOD = 1e9 + 7;
public:
    int countSteppingNumbers(string low, string high) {
        long long h = count(high);
        int l = count(low);
        int o = ok(high);
        return (h + o + MOD - l) % MOD;
    }
    int count(const string& value) {
        if (value.size() == 1) {
            return value[0] - '1';
        }

        int n = value.size();
        vector<array<int, 10>> counts(n);
        counts[0].fill(1);
        for (int i = 1; i < n; ++i) {
            counts[i][0] = counts[i - 1][1];
            counts[i][9] = counts[i - 1][8];
            for (int j = 1; j < 9; ++j) {
                counts[i][j] = counts[i - 1][j - 1] + counts[i - 1][j + 1];
                if (counts[i][j] >= MOD) counts[i][j] -= MOD;
            }
        }
        long long result = 0;
        for (int i = 0; i < n - 1; ++i) {
            result = accumulate(counts[i].begin() + 1, counts[i].end(), result);
        }
        for (int j = 1; j < value[0] - '0'; ++j) {
            result += counts[n - 1][j];
        }
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < value[i] - '0'; ++j) {
                if (abs(value[i - 1] - '0' - j) == 1) {
                    result += counts[n - 1 - i][j];
                }
            }
            if (abs(value[i] - value[i - 1]) != 1) break;
        }
        return result % MOD;
    }
    int ok(const string& value) {
        for (int i = 1; i < value.size(); ++i) {
            if (abs(value[i] - value[i - 1]) != 1) return 0;
        }
        return 1;
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
    auto actual = s.countSteppingNumbers("1", "11");
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test1)
{
    Solution s;
    auto actual = s.countSteppingNumbers("90", "101");
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

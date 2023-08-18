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
    static constexpr int MOD = 1e9 + 7;
public:
    int countPalindromes(string s) {
        int count1[10] = { 0 };
        int count2[10][10] = { 0 };
        int count3[10][10][10] = { 0 };
        int count4[10][10][10] = { 0 };
        long long result = 0;
        for (auto ch : s) {
            int x = ch - '0';
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    result += count4[x][i][j];
                }
            }
            result %= MOD;
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    count4[i][x][j] += count3[i][x][j];
                    if (count4[i][x][j] >= MOD) count4[i][x][j] -= MOD;
                }
            }
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 10; ++j) {
                    count3[i][j][x] += count2[i][j];
                    if (count3[i][j][x] >= MOD) count3[i][j][x] -= MOD;
                }
            }
            for (int i = 0; i < 10; ++i) {
                count2[i][x] += count1[i];
                if (count2[i][x] >= MOD) count2[i][x] -= MOD;
            }
            ++count1[x];
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
    auto actual = s.countPalindromes("103301");
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}


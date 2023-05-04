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
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        auto it = lower_bound(fruits.begin(), fruits.end(), vector<int>({startPos}));
        auto jt = it;
        int result = 0;
        for (; jt != fruits.end() && (*jt)[0] <= startPos + k; ++jt) {
            result += (*jt)[1];
        }
        if (jt != fruits.begin()) {
            --jt;
            auto kt = it;
            int r = result;
            while (kt != fruits.begin()) {
                --kt;
                if ((startPos - (*kt)[0]) * 2 > k) break;
                r += (*kt)[1];
                auto limit = startPos + (k - (startPos - (*kt)[0]) * 2);
                for (; jt != it && (*jt)[0] > limit; --jt) {
                    r -= (*jt)[1];
                }
                result = max(result, r);
            }
        }

        if (it != fruits.end() && (*it)[0] == startPos) {
            ++it;
        }
        jt = lower_bound(fruits.begin(), fruits.end(), vector<int>({ startPos - k }));
        int r = 0;
        auto kt = jt;
        for (; kt != it; ++kt) r += (*kt)[1];
        result = max(result, r);

        kt = it;
        if (kt != fruits.end()) {
            for (; kt != fruits.end() && ((*kt)[0] - startPos) * 2 <= k; ++kt) {
                r += (*kt)[1];
                auto limit = startPos - (k - ((*kt)[0] - startPos) * 2);
                for (; jt != it && (*jt)[0] < limit; ++jt) {
                    r -= (*jt)[1];
                }
                result = max(result, r);
            }
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
    vector<vector<int>> fruits = {{2, 8}, {6, 3}, {8, 6}};
    Solution s;
    auto actual = s.maxTotalFruits(fruits, 5, 4);
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> fruits = { {0,7},{7,4},{9,10},{12,6},{14,8},{16,5},{17,8},{19,4},{20,1},{21,3},{24,3},{25,3},{26,1},{28,10},{30,9},{31,6},{32,1},{37,5},{40,9} };
    Solution s;
    auto actual = s.maxTotalFruits(fruits, 21, 30);
    decltype(actual) expect = 71;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> fruits = { {5,8},{7,7},{8,7},{15,5},{18,8},{19,3},{25,4},{26,1},{34,10},{38,3},{39,4},{40,5} };
    Solution s;
    auto actual = s.maxTotalFruits(fruits, 6, 19);
    decltype(actual) expect = 38;
    EXPECT_EQ(expect, actual);
}
}

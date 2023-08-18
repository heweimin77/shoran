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
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        int m = robot.size(), n = factory.size();
        vector<vector<long long>> results(m, vector<long long>(n, LLONG_MAX));
        if (factory[0][1] > 0)
            results[0][0] = abs(robot[0] - factory[0][0]);
        for (int j = 1; j < n; ++j) {
            if (factory[j][1] > 0)
                results[0][j] = min(abs((long long)robot[0] - factory[j][0]), results[0][j - 1]);
            else
                results[0][j] = results[0][j - 1];
        }

        for (int i = 1; i < m; ++i) {
            if (i < factory[0][1]) {
                results[i][0] = results[i - 1][0] + abs(robot[i] - factory[0][0]);
            }

            for (int j = 1; j < n; ++j) {
                long long r = results[i][j - 1];
                long long rr = 0;
                int limit = max(0, i - factory[j][1] + 1);
                for (int ii = i; ii >= limit; --ii) {
                    rr += abs((long long)robot[ii] - factory[j][0]);
                    if (ii > 0) {
                        if (results[ii - 1][j - 1] != LLONG_MAX) {
                            r = min(r, rr + results[ii - 1][j - 1]);
                        }
                    } else {
                        r = min(r, rr);
                    }
                }
                results[i][j] = r;
            }
        }
        return results.back().back();
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
    vector<int> robot = { 0,4,6 };
    vector<vector<int>> factory = { {2,2}, {6,2} };
    Solution s;
    auto actual = s.minimumTotalDistance(robot, factory);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> robot = { 9,11,99,101 };
    vector<vector<int>> factory = { {10,1}, {7,1}, {14,1}, {100,1}, {96,1}, {103,1} };
    Solution s;
    auto actual = s.minimumTotalDistance(robot, factory);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}


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
    int maximumRobots(vector<int> &chargeTimes, vector<int> &runningCosts, long long budget)
    {
        int r = 0;
        int n = chargeTimes.size();
        priority_queue<pair<int, int>> charges;
        int j = -1;
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            while (!charges.empty() && charges.top().second < i) charges.pop();
            for (++j; j < n; ++j) {
                charges.push({ chargeTimes[j], j });
                sum += runningCosts[j];
                if (charges.top().first + sum * (j - i + 1) > budget) break;
                r = max(r, j - i + 1);
            }
            if (j == n) break;
            sum -= runningCosts[i];
        }
        return r;
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
    vector<int> chargeTimes = { 3,6,1,3,4 };
    vector<int> runningCosts = { 2,1,3,4,5 };
    Solution s;
    auto actual = s.maximumRobots(chargeTimes, runningCosts, 25);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> chargeTimes = { 8,76,74,9,75,71,71,42,15,58,88,38,56,59,10,11 };
    vector<int> runningCosts = { 1,92,41,63,22,37,37,8,68,97,39,59,45,50,29,37 };
    Solution s;
    auto actual = s.maximumRobots(chargeTimes, runningCosts, 412);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}


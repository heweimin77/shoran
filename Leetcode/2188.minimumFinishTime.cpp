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
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        int limit = (tires[0][0] + changeTime) * numLaps;
        int costs[32];
        fill(costs, costs + 32, INT_MAX);
        costs[0] = 0;
        for (auto& t : tires) {
            int ct = 0;
            for (int cost = t[0], i = 1; cost < limit; cost *= t[1], ++i) {
                costs[i] = min(costs[i], cost + ct);
                ct += cost;
            }
        }
        int cnt = 1;
        while (costs[cnt] != INT_MAX) ++cnt;

        vector<int> results(numLaps + 1);
        results[0] = -changeTime;
        results[1] = costs[1];
        for (int i = 2; i <= numLaps; ++i) {
            int r = results[i - 1] + changeTime + costs[1];
            for (int j = 2; j <= i && j < cnt; ++j) {
                r = min(r, results[i - j] + changeTime + costs[j]);
            }
            results[i] = r;
            //cout << i << ", " << results[i] << endl;
        }
        return results[numLaps];
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
    vector<vector<int>> tires = { {2,3}, {3,4} };
    Solution s;
    auto actual = s.minimumFinishTime(tires, 5, 4);
    decltype(actual) expect = 21;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> tires = { {1,10}, {2,2}, {3,4} };
    Solution s;
    auto actual = s.minimumFinishTime(tires, 6, 5);
    decltype(actual) expect = 25;
    EXPECT_EQ(expect, actual);
}

}

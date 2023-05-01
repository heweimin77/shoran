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
    int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime)
    {
        vector<int> degrees(n);
        for (int i = 0; i < n; ++i) {
            if (manager[i] != -1) {
                ++degrees[manager[i]];
            }
        }
        queue<int> q;
        vector<int> results(n);
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            auto next = manager[now];
            if (next >= 0) {
                results[next] = max(results[next], results[now] + informTime[next]);
                if (--degrees[next] == 0) {
                    q.push(next);
                }
            }
        }
        return results[headID];
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
    vector<int> manager = { 2,2,-1,2,2,2 };
    vector<int> informTime = { 0,0,1,0,0,0 };
    Solution s;
    auto actual = s.numOfMinutes(6, 2, manager, informTime);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<int> manager = { 1,2,3,4,5,6,-1 };
    vector<int> informTime = { 0,6,5,4,3,2,1 };
    Solution s;
    auto actual = s.numOfMinutes(7, 6, manager, informTime);
    decltype(actual) expect = 21;
    EXPECT_EQ(expect, actual);
}
}

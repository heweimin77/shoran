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
    int hardestWorker(int n, vector<vector<int>>& logs) {
        int mid = logs[0][0];
        int mtime = logs[0][1];
        int t = 0;
        for (auto& log : logs) {
            if (log[1] - t > mtime || (log[1] - t == mtime && log[0] < mid)) {
                mtime = log[1] - t;
                mid = log[0];
            }
            t = log[1];
        }
        return mid;
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
    vector<vector<int>> logs = {{0, 3}, {2, 5}, {0, 9}, {1, 15}};
    Solution s;
    auto actual = s.hardestWorker(10, logs);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}

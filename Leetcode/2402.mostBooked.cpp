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
    int mostBooked(int n, vector<vector<int>> &meetings)
    {
        priority_queue<int, vector<int>, greater<int>> emeeting;
        for (int i = 0; i < n; ++i) emeeting.push(i);
        vector<int> counts(n);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> meets;

        long long now = 0;
        sort(meetings.begin(), meetings.end());
        for (auto &m : meetings) {
            if (m[0] > now) {
                now = m[0];
            }
            if (emeeting.empty() && meets.top().first > now) {
                now = meets.top().first;
            }
            while (!meets.empty() && meets.top().first <= now) {
                emeeting.push(meets.top().second);
                meets.pop();
            }
            int e = emeeting.top();
            emeeting.pop();
            ++counts[e];
            meets.push({ now + m[1] - m[0], e });
        }

        int mcount = 0;
        int r = 0;
        for (int i = 0; i < n; ++i) {
            if (counts[i] > mcount) {
                mcount = counts[i];
                r = i;
            }
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

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> nums = { {0,10}, {1,5}, {2,7}, {3,4} };
    Solution s;
    auto actual = s.mostBooked(2, nums);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
}
}


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
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        stable_sort(time.begin(), time.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            return lhs[0] + lhs[2] < rhs[0] + rhs[2];
            });

        int t = 0;
        priority_queue<int> lline, rline;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> picks;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> puts;

        for (int i = 0; i < k; ++i) lline.push(i);
              
        int result = 0;

        while (n > 0 || !rline.empty() || !puts.empty() || !picks.empty()) {
            if (!rline.empty()) {
                int i = rline.top();
                rline.pop();
                t += time[i][2];
                puts.push({t + time[i][3], i}),
                result = t;
            } else if (!lline.empty() && n > 0) {
                int i = lline.top();
                lline.pop();
                t += time[i][0];
                picks.push({ t + time[i][1], i });
                --n;
            } else {
                int next = INT_MAX;
                if (!puts.empty()) {
                    next = min(next, puts.top().first);
                }
                if (!picks.empty()) {
                    next = min(next, picks.top().first);
                }
                t = next;
            }
            while (!picks.empty() && picks.top().first <= t) {
                rline.push(picks.top().second);
                picks.pop();
            }
            while (!puts.empty() && puts.top().first <= t) {
                lline.push(puts.top().second);
                puts.pop();
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

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> time = { {1, 1, 2, 1}, {1, 1, 3, 1}, {1, 1, 4, 1} };
    Solution s;
    auto actual = s.findCrossingTime(1, 3, time);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}

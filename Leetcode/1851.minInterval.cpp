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
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        sort(intervals.begin(), intervals.end());
        int t = 0;
        int v = -1;
        vector<pair<int, int>> results;
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        auto it = intervals.begin();
        while (!q.empty() || it != intervals.end()) {
            t = INT_MAX;
            if (!q.empty()) {
                t = q.top().second;
            }
            if (it != intervals.end()) {
                t = min(t, (*it)[0]);
            }
            if (it != intervals.end()) {
                if (t >= (*it)[0]) {
                    q.push({ (*it)[1] - (*it)[0] + 1, (*it)[1] + 1 });
                    ++it;
                }
            }
            while (!q.empty() && q.top().second <= t) q.pop();
            if (q.empty()) {
                v = -1;
                results.push_back({ t, v });
            } else {
                if (v != q.top().first) {
                    v = q.top().first;
                    results.push_back({ t, v });
                }
            }
        }
        vector<int> rs;
        for (auto q : queries) {
            pair<int, int> x = { q, INT_MAX };
            auto it = lower_bound(results.begin(), results.end(), x);
            if (it == results.begin()) {
                rs.push_back(-1);
            } else {
                --it;
                rs.push_back(it->second);
            }
        }
        return rs;
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
    vector<vector<int>> intervals = { {1, 4}, {2, 4}, {3, 6}, {4, 4} };
    vector<int> queries = { 2,3,4,5 };
    Solution s;
    auto actual = s.minInterval(intervals, queries);
    decltype(actual) expect = {3, 3, 1, 4};
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> intervals = { {9, 9}, {6, 7}, {5, 6}, {2, 5}, {3, 3} };
    vector<int> queries = { 6,1,1,1,9 };
    Solution s;
    auto actual = s.minInterval(intervals, queries);
    decltype(actual) expect = { 2, -1, -1, -1, 1};
    EXPECT_EQ_CONTAINER(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> intervals = { {9, 9}, {6, 6}, {9, 10}, {1, 5}, {1, 5} };
    vector<int> queries = { 7,1,9,8,1 };
    Solution s;
    auto actual = s.minInterval(intervals, queries);
    decltype(actual) expect = { -1,5,1,-1,5 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}

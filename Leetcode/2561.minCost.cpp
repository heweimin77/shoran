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

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        int mx = min(*min_element(basket1.begin(), basket1.end()), *min_element(basket2.begin(), basket2.end())) * 2;
        unordered_map<int, int> counts;
        for (auto n : basket1) ++counts[n];
        for (auto n : basket2) --counts[n];

        vector<pair<int,int>> pos, neg;
        for (auto& r : counts) {
            if (r.second == 0) continue;
            if (r.second & 1) return -1;

            if (r.second < 0) {
                neg.push_back({ r.first, -r.second / 2});
            } else {
                pos.push_back({ r.first, r.second / 2});
            }
        }
        sort(pos.begin(), pos.end());
        sort(neg.begin(), neg.end(), greater<pair<int, int>>());
        int result = 0;
        for (int i = 0, j = 0; i < pos.size() && j < neg.size(); ) {
            if (pos[i].second == neg[j].second) {
                result += min(min(pos[i].first, neg[j].first), mx) * neg[j].second;
                ++i, ++j;
            } else if (pos[i].second < neg[j].second) {
                result += min(min(pos[i].first, neg[j].first), mx) * pos[i].second;
                neg[j].second -= pos[i].second;
                ++i;
            } else {
                result += min(min(pos[i].first, neg[j].first), mx) * neg[j].second;
                pos[i].second -= neg[j].second;
                ++j;
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
    vector<int> basket1 = { 4,2,2,2 };
    vector<int> basket2 = { 1,4,1,2 };
    Solution s;
    auto actual = s.minCost(basket1, basket2);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> basket1 = { 84,80,43,8,80,88,43,14,100,88 };
    vector<int> basket2 = { 32,32,42,68,68,100,42,84,14,8 };
    Solution s;
    auto actual = s.minCost(basket1, basket2);
    decltype(actual) expect = 48;
    EXPECT_EQ(expect, actual);
}
}

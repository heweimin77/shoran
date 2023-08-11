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
    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        long long result = 0;
        function<pair<long long, long long>(int, int)> dfs = [&](int now, int parent)->pair<long long, long long> {
            long long p = price[now], smax1 = p, smax2 = 0;
            for (int next : adjs[now]) {
                if (next == parent) continue;
                auto [s1, s2] = dfs(next, now);
                result = max(result, smax1 + s2);
                result = max(result, smax2 + s1);
                smax1 = max(smax1, s1 + p);
                smax2 = max(smax2, s2 + p);
            }
            return { smax1, smax2 };
        };
        dfs(0, -1);
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
    vector<vector<int>> edges = { {0,1}, {1,2}, {1,3}, {3,4}, {3,5} };
    vector<int> price = { 9,8,7,6,10,5 };
    Solution s;
    auto actual = s.maxOutput(6, edges, price);
    decltype(actual) expect = 24;
    EXPECT_EQ(expect, actual);
}
}

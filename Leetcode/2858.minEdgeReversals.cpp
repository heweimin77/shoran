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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<int> minEdgeReversals(int n, vector<vector<int>>& edges) {
        
        vector<vector<int>> nexts(n), prevs(n);
        vector<int> degree(n);
        for (auto& e : edges) {
            nexts[e[0]].push_back(e[1]);
            prevs[e[1]].push_back(e[0]);
            ++degree[e[1]];
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) if (degree[i] == 0) q.push(i);
        vector<int> results(n);
        vector<int> deltas(n);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            int r = 0;
            for (auto p : prevs[now]) {
                r += results[p] + 1;
            }
            for (auto p : prevs[now]) {
                deltas[p] = r - results[p] - 1;
            }
            results[now] = r;
            for (auto n : nexts[now]) {
                if (--degree[n] == 0) q.push(n);
            }
        }

        vector<bool> visited(n);
        function<void(int)> dfs = [&](int now) {
            if (visited[now]) return;
            for (auto n : nexts[now]) {
                dfs(n);
                deltas[now] += deltas[n];
            }
            visited[now] = true;
        };
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;
            dfs(i);
        }
        for (int i = 0; i < n; ++i) results[i] += deltas[i];

        return results;
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
    vector<vector<int>> edges = {{2,0}, {2,1}, {1,3}};
    Solution s;
    auto actual = s.minEdgeReversals(4, edges);
    decltype(actual) expect = { 1,1,0,2 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

TEST_F(TestSolution, Test2)
{
    vector<vector<int>> edges = { {0,3}, {1,2}, {2,3} };
    Solution s;
    auto actual = s.minEdgeReversals(4, edges);
    decltype(actual) expect = { 2,1,2,3 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> edges = { {0,1}, {2,0}, {0,4}, {3,4} };
    Solution s;
    auto actual = s.minEdgeReversals(5, edges);
    decltype(actual) expect = { 2,3,1,2,3 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}

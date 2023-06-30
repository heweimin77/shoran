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
#include <stack>
#include <numeric>
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int chaseGame(vector<vector<int>>& edges, int startA, int startB) {
        int n = edges.size();
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            --e[0], --e[1];
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        --startA, --startB;

        vector<int> loops;
        findLoop(adjs, loops);

        vector<int> adistances(n, -1), bdistances(n, -1);
        getDistances(adjs, startA, adistances);
        if (adistances[startB] == 1) return 1;
        getDistances(adjs, startB, bdistances);

        vector<bool> isloop(n);
        for (auto x : loops) {
            isloop[x] = true;
        }
        
        int result = 0;
        vector<bool> visited(n);
        queue<int> q;
        q.push(startB);
        visited[startB] = true;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            result = max(result, adistances[now]);
            if (adistances[now] > bdistances[now] + 1) {
                if (isloop[now] && loops.size() > 3) return -1;
                for (auto next : adjs[now]) {
                    if (visited[next]) continue;
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        return result;
    }
    void getDistances(vector<vector<int>> &adjs, int start, vector<int> &distances) {
        distances[start] = 0;
        queue<int> q;
        q.push(start);
        while (!q.empty()) {
            int now = q.front();
            int d = distances[now];
            q.pop();
            for (auto next : adjs[now]) {
                if (distances[next] < 0) {
                    distances[next] = d + 1;
                    q.push(next);
                }
            }
        }
    }
    void findLoop(vector<vector<int>> &adjs, vector<int> &loops) {
        vector<int> colors(adjs.size());
        stack<int> s;
        dfs(adjs, loops, colors, s, 0, -1);
    }
    bool dfs(vector<vector<int>> &adjs, vector<int>& loops, vector<int> &colors, stack<int> &s, int now, int pre) {
        if (colors[now] == 1) {
            loops.push_back(now);
            while (s.top() != now) {
                loops.push_back(s.top());
                s.pop();
            }
            return true;
        }
        colors[now] = 1;
        s.push(now);
        for (auto next : adjs[now]) {
            if (next == pre) continue;
            if (dfs(adjs, loops, colors, s, next, now)) return true;
        }
        s.pop();
        colors[now] = 2;
        return false;
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
    vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {2, 5}, {5, 6}};
    Solution s;
    auto actual = s.chaseGame(edges, 3, 5);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {3, 1}, {3, 6}, {2, 4}, {4, 5}, {5, 8}, {4, 7} };
    Solution s;
    auto actual = s.chaseGame(edges, 6, 7);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {3, 4}, {4, 1} };
    Solution s;
    auto actual = s.chaseGame(edges, 1, 3);
    decltype(actual) expect = -1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {3, 1}, {3, 6}, {2, 4}, {4, 5}, {5, 8}, {4, 7} };
    Solution s;
    auto actual = s.chaseGame(edges, 8, 7);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> edges = { {1, 2}, {2, 3}, {3, 4}, {2, 5}, {2, 6}, {2, 7}, {5, 8}, {3, 9}, {2, 10}, {1, 10} };
    Solution s;
    auto actual = s.chaseGame(edges, 1, 4);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}


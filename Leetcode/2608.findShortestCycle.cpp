#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
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
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        unsigned result = -1;
        for (int i = 0; i < n; ++i) {
            result = min(result, getShortCycle(i, n, adjs));
            //cout << i << ": " << result << endl;
        }
        return result;
    }
    unsigned getShortCycle(int i, int n, vector<vector<int>> &adjs) {
        vector<int> distance(n, -1);
        vector<int> parent(n, -1);
        vector<bool> visited(n);
        distance[i] = 0;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int now = q.front();
            visited[now] = true;
            q.pop();
            for (auto next : adjs[now]) {
                if (next == parent[now]) continue;
                if (visited[next]) {
                    return distance[now] + distance[next] + 1;
                }
                if (distance[next] < 0) {
                    distance[next] = distance[now] + 1;
                    parent[next] = now;
                    q.push(next);
                }
            }
        }

        return -1;
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
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,0}, {3,4}, {4,5}, {5,6}, {6,3} };
    Solution s;
    auto actual = s.findShortestCycle(7, edges);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> edges = { {0,1}, {0,2} };
    Solution s;
    auto actual = s.findShortestCycle(4, edges);
    decltype(actual) expect = -1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> edges = { {4,2}, {5,1}, {5,0}, {0,3}, {5,2}, {1,4}, {1,3}, {3,4} };
    Solution s;
    auto actual = s.findShortestCycle(6, edges);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

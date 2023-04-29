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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    long long minimumFuelCost(vector<vector<int>> &roads, int seats)
    {
        int n = roads.size() + 1;
        vector<vector<int>> adjs(n);
        for (auto &r : roads) {
            adjs[r[0]].push_back(r[1]);
            adjs[r[1]].push_back(r[0]);
        }
        vector<int> parent(n, -1);
        stack<int> ss;
        ss.push(0);
        while (!ss.empty()) {
            int p = ss.top();
            ss.pop();
            for (auto child : adjs[p]) {
                if (child == parent[p]) continue;
                parent[child] = p;
                ss.push(child);
            }
        }

        queue<int> q;
        vector<int> degree(n);
        degree[0] = n;
        for (int i = 1; i < n; ++i) {
            degree[i] = adjs[i].size() - 1;
            if (degree[i] == 0) {
                q.push(i);
            }
        }
        long long result = 0;
        vector<int> counts(n, 1);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            result += (counts[now] + seats - 1) / seats;
            int p = parent[now];
            counts[p] += counts[now];
            if (--degree[p] == 0) {
                q.push(p);
            }
        }
        return result;
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
    vector<vector<int>> roads = {{0, 1}, {0, 2}, {0, 3}};
    Solution s;
    auto actual = s.minimumFuelCost(roads, 5);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
    
}

}

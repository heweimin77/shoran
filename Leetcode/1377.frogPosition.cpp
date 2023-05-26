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
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if (n == 1) return 1.0;
        if (target == 1) return 0.0;
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0] - 1].push_back(e[1] - 1);
            adjs[e[1] - 1].push_back(e[0] - 1);
        }
        vector<int> paths;
        traverse(adjs, 0, -1, target - 1, paths);

        if (paths.size() > t + 1) return 0.0;
        if (paths.size() < t + 1 && adjs[target - 1].size() > 1) return 0.0;
        double result = 1.0 / adjs[0].size();
        for (int i = 1; i < paths.size() - 1; ++i) {
            result /= adjs[paths[i]].size() - 1;
        }
        return result;
    }
    bool traverse(vector<vector<int>>& adjs, int now, int parent, int target, vector<int> &paths) {
        paths.push_back(now);
        if (now == target) {
            return true;
        }
        for (auto next : adjs[now]) {
            if (next == parent) continue;
            if (traverse(adjs, next, now, target, paths)) {
                return true;
            }
        }
        paths.pop_back();
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
    vector<vector<int>> edges = {{1, 2}, {1, 3}, {1, 7}, {2, 4}, {2, 6}, {3, 5}};
    Solution s;
    auto actual = s.frogPosition(7, edges, 2, 4);
    decltype(actual) expect = 1.0/6.0;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> edges = { {2, 1},{3, 2},{4, 3},{5, 3},{6, 5},{7, 3},{8, 4},{9, 5} };
    Solution s;
    auto actual = s.frogPosition(9, edges, 9, 1);
    decltype(actual) expect = 0.0;
    EXPECT_EQ(expect, actual);
}
}

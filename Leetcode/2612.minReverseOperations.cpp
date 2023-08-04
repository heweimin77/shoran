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
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> results(n, -1);
        vector<bool> ban(n);
        for (auto b : banned) ban[b] = true;
        results[p] = 0;
        map<int, int> visited;
        visited[p] = p + 1;
        if (k == 1) return results;
        bool skip = (k & 1);
        if (skip) {
            for (int i = (p & 1); i < n; i += 2) {
                ban[i] = true;
            }
        }

        queue<int> q;
        q.push(p);
        while (!q.empty()) {
            auto now = q.front();
            int nv = results[now] + 1;
            q.pop();
            // move left
            int xmin = max(now + 1, k - 1 - now);
            int xmax = min(now + k, (n + 1) / 2 + 1 - k);
            getNexts(q, xmin, xmax, results, ban, visited, now);

            // move right
            xmin = max(now - k + 1, k - 1 - now);
            xmax = min(now, (n + 1) / 2 + 1 - k);
            getNexts(q, xmin, xmax, results, ban, visited, now);
        }
        return results;
    }
    void getNexts(queue<int> &q, int xmin, int xmax, vector<int> &results, vector<bool> &ban, map<int, int> &visited, int now) {

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
    vector<int> banned = { 1,2 };
    Solution s;
    auto actual = s.minReverseOperations(4, 0, banned, 4);
    decltype(actual) expect = { 0,-1,-1,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

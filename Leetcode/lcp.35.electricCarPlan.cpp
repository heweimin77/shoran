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
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge) {
        int n = charge.size();
        vector<vector<pair<int,int>>> adjs(n);
        for (auto& p : paths) {
            adjs[p[0]].push_back({ p[1], p[2] });
            adjs[p[1]].push_back({ p[0], p[2] });
        }

        unsigned int results[100][101];
        memset(results, -1, sizeof(results));
        priority_queue < vector<int>, vector<vector<int>>, greater<vector<int>>> q;
        results[start][0] = 0;
        q.push({ 0, start, 0 });

        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now[0] > results[now[1]][now[2]]) continue;
            if (now[1] == end) return now[0];

            // charge
            for (int i = 1; i <= cnt - now[2]; ++i) {
                unsigned int nv = now[0] + i * charge[now[1]];
                if (nv < results[now[1]][now[2] + i]) {
                    results[now[1]][now[2] + i] = nv;
                    q.push({ (int)nv, now[1], now[2] + i });
                }
            }

            for (auto next : adjs[now[1]]) {
                if (now[2] < next.second) continue;
                unsigned int nv = now[0] + next.second;
                if (nv < results[next.first][now[2] - next.second]) {
                    results[next.first][now[2] - next.second] = nv;
                    q.push({ (int)nv, next.first, now[2] - next.second });
                }
            }
        }

        return 0;
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
    vector<vector<int>> paths = { { 1,3,3}, {3,2,1}, {2,1,3}, {0,1,4}, {3,0,5} };
    vector<int> charge = { 2,10,4,1 };
    Solution s;
    auto actual = s.electricCarPlan(paths, 6, 1, 0, charge);
    decltype(actual) expect = 43;
    EXPECT_EQ(expect, actual);
}
}

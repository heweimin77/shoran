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
    int countCompleteComponents(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adjs(n);
        for (auto &e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i]) continue;
            vector<int> ps;
            ps.push_back(i);
            visited[i] = true;
            for (int j = 0; j < ps.size(); ++j) {
                auto now = ps[j];
                for (auto next : adjs[now]) {
                    if (visited[next]) continue;
                    ps.push_back(next);
                    visited[next] = true;
                }
            }
            bool ok = true;
            int degree = ps.size() - 1;
            for (auto p : ps) {
                if (degree != adjs[p].size()) {
                    ok = false;
                    break;
                }
            }
            if (ok) ++result;
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

TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> edges = { {0, 1}, {0, 2}, {1, 2}, {3, 4} };
    Solution s;
    auto actual = s.countCompleteComponents(6, edges);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

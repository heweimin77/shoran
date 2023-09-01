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
#include <stack>
#include "support.h"

using namespace std;

namespace {

class Solution {
#define MAKEPOS(x, y)   (((x) << 16) | (y))
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        vector<int> degree(n);
        vector<vector<int>> adjs(n);
        unordered_set<int> connected;
        for (auto& e : edges) {
            --e[0], --e[1];
            ++degree[e[0]], ++degree[e[1]];
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
            connected.insert(MAKEPOS(e[0], e[1]));
            connected.insert(MAKEPOS(e[1], e[0]));
        }


        for (auto& adj : adjs) {
            sort(adj.begin(), adj.end(), [&](int lhs, int rhs) {
                return degree[lhs] < degree[rhs];
                });
        }

        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&](int lhs, int rhs) {
            return degree[lhs] < degree[rhs];
            });

        int result = INT_MAX;
        for (int i = 0; i < n; ++i) {
            auto& adj = adjs[indexes[i]];
            int r = degree[indexes[i]];
            if (r * 3 >= result) continue;
            for (int k = 0; k < adj.size(); ++k) {
                if (r + degree[adj[k]] + degree[adj[k]] >= result) break;
                r += degree[adj[k]];
                for (int kk = k + 1; kk < adj.size(); ++kk) {
                    if (r + degree[adj[kk]] >= result) break;
                    if (connected.count(MAKEPOS(adj[k], adj[kk])) == 0) continue;
                    result = min(result, r + degree[adj[kk]]);
                    //cout << result << endl;
                }
                r -= degree[adj[k]];
            }
        }
        return result == INT_MAX ? -1 : result - 6;

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
    vector<vector<int>> edges = { {1,2}, {1,3}, {3,2}, {4,1}, {5,2}, {3,6} };
    Solution s;
    auto actual = s.minTrioDegree(6, edges);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test1)
{
    vector<vector<int>> edges = { {1,3}, {4,1}, {4,3}, {2,5}, {5,6}, {6,7}, {7,5}, {2,6} };
    Solution s;
    auto actual = s.minTrioDegree(7, edges);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
}

}

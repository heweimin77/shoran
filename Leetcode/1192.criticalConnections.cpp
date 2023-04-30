#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {
        vector<vector<int>> adjs(n);
        for (auto &e : connections) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        
        vector<int> dfn(n);
        vector<int> low(n);
        int stamp = 1;
        for (int i = 0; i < n; ++i) {
            if (dfn[i] > 0) continue;
            tarjan_bridge(adjs, 0, -1, dfn, low, stamp);
        }
        

        vector<vector<int>> results;
        for (auto &e : connections) {
            if (dfn[e[0]] < low[e[1]] || dfn[e[1]] < low[e[0]]) {
                results.push_back(e);
            }
        }
        return results;
    }
    void tarjan_bridge(vector<vector<int>> &adjs, int i, int pre, vector<int> &dfn, vector<int> &low, int &stamp)
    {
        dfn[i] = low[i] = stamp++;
        for (auto next : adjs[i]) {
            if (next == pre) continue;
            if (dfn[next] == 0) {
                tarjan_bridge(adjs, next, i, dfn, low, stamp);
            }
            low[i] = min(low[i], low[next]);
        }
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
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    Solution s;
    auto actual = s.criticalConnections(4, connections);
    decltype(actual) expect = { {1,3} };
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
}

}

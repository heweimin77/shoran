#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>> &rowConditions, vector<vector<int>> &colConditions)
    {
        vector<int> row(k), col(k);
        if (!getLine(rowConditions, k, row)) return {};
        if (!getLine(colConditions, k, col)) return {};

        vector<vector<int>> results(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            results[row[i]][col[i]] = i + 1;
        }
        return results;
    }
    bool getLine(vector<vector<int>> &conditions, int k, vector<int> &line)  {
        vector<vector<int>> adjs(k);
        for (auto &c : conditions) {
            adjs[c[0]-1].push_back(c[1]-1);
        }
        fill(line.begin(), line.end(), -1);

        int n = k;
        function<bool(int)> dfs = [&](int now)->bool {
            line[now] = INT_MAX;
            for (auto next : adjs[now]) {
                if (line[next] == INT_MAX) return false;
                if (line[next] >= 0) continue;
                if(!dfs(next)) return false;
            }
            line[now] = --n;
            return true;
        };

        for (int i = 0; i < k; ++i) {
            if (line[i] >= 0) continue;
            if (!dfs(i)) return false;
        }
        return true;
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
    vector<vector<int>> rowConditions = { {1,2}, {3,2} };
    vector<vector<int>> colConditions = { {2,1}, {3,2} };
    Solution s;
    auto actual = s.buildMatrix(3, rowConditions, colConditions);
    decltype(actual) expect = { {3,0,0}, {0,0,1}, {0,2,0} };
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
}

}


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
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        int n = queries.size();
        vector<int> indexes(n);
        iota(indexes.begin(), indexes.end(), 0);
        sort(indexes.begin(), indexes.end(), [&](int lhs, int rhs) {
            return queries[lhs] < queries[rhs];
            });
        int result = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
        q.push({ grid[0][0], 0, 0 });
        grid[0][0] = INT_MAX;

        int deltas[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        vector<int> results(n);
        for (int i = 0; i < n; ++i) {
            int limit = queries[indexes[i]];
            while (!q.empty() && q.top()[0] < limit) {
                auto now = q.top();
                q.pop();
                ++result;
                for (auto& d : deltas) {
                    int nx = now[1] + d[0];
                    int ny = now[2] + d[1];
                    if (nx < 0 || nx >= grid.size()) continue;
                    if (ny < 0 || ny >= grid[0].size()) continue;
                    if (grid[nx][ny] == INT_MAX) continue;
                    q.push({ grid[nx][ny], nx, ny });
                    grid[nx][ny] = INT_MAX;
                }
            }
            results[indexes[i]] = result;
        }
        return results;
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
    vector<vector<int>> grid = { {1,2,3}, {2,5,7}, {3,5,1} };
    vector<int> queries = { 5,6,2 };
    Solution s;
    auto actual = s.maxPoints(grid, queries);
    decltype(actual) expect = {5, 8, 1};
    EXPECT_EQ_CONTAINER(expect, actual);
}
}


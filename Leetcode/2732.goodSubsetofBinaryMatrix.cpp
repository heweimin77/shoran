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
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid[0].size();
        vector<int> visited(1 << n, -1);
        int i = 0;
        for (auto& row : grid) {
            int v = 0;
            for (auto x : row) {
                v <<= 1;
                v |= x;
            }
            if (v == 0) return { i };
            visited[v] = i++;
        }
        for (int i = 0; i < visited.size(); ++i) {
            if (visited[i] < 0) continue;
            for (int j = 0; j < visited.size(); ++j) {
                if (visited[j] < 0) continue;
                if ((i & j) == 0) {
                    if (visited[i] < visited[j]) {
                        return { visited[i], visited[j] };
                    } else {
                        return { visited[j], visited[i] };
                    }

                }
            }
        }
        return {};
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
    vector<vector<int>> grid = {{0, 1, 1, 0}, {0, 0, 0, 1}, {1, 1, 1, 1}};
    Solution s;
    auto actual = s.goodSubsetofBinaryMatrix(grid);
    decltype(actual) expect = {0, 1};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

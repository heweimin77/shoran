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
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<unordered_map<int, int>> adjs(n);
        vector<int> degree(n);
        for (auto& e : edges) {
            --e[0], --e[1];
            ++adjs[e[0]][e[1]];
            ++adjs[e[1]][e[0]];
            ++degree[e[0]];
            ++degree[e[1]];
        }

        vector<int> sums(edges.size() + 1);
        for (auto d : degree) {
            ++sums[d];
        }
        int s = 0;
        for (int i = sums.size() - 1; i >= 0; --i) {
            s += sums[i];
            sums[i] = s;
        }

        vector<int> results;
        for (auto q : queries) {
            int result = 0;
            for (int i = 0; i < n; ++i) {
                if (degree[i] > q) {
                    result += n - 1;
                    continue;
                }
                int x = q - degree[i] + 1;
                result += sums[x];
                if (degree[i] >= x) --result;
                for (auto& r: adjs[i]) {
                    if (degree[r.first] >= x && degree[r.first] - r.second < x) {
                        --result;
                    }
                }
            }
            results.push_back(result / 2);
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
    vector<vector<int>> edges = { {1,2}, {2,4}, {1,3}, {2,3}, {2,1} };
    vector<int> queries = { 2 };// {2, 3};
    Solution s;
    auto actual = s.countPairs(4, edges, queries);
    decltype(actual) expect = { 6 };// { 6, 5};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

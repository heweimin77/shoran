#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<unordered_set<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].insert(e[1]);
            adjs[e[1]].insert(e[0]);
        }
        deleteNocoinLeaf(n, adjs, coins);
        deleteLeaf(n, adjs);
        deleteLeaf(n, adjs);
        return getResult(n, adjs);
    }
    void deleteNocoinLeaf(int n, vector<unordered_set<int>>& adjs, vector<int>& coins) {
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (coins[i] == 0 && adjs[i].size() == 1) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            int leaf = q.front();
            q.pop();
            if (adjs[leaf].empty()) continue;
            int next = *adjs[leaf].begin();
            adjs[leaf].clear();
            adjs[next].erase(leaf);
            if (coins[next] == 0 && adjs[next].size() == 1) {
                q.push(next);
            }
        }
    }
    void deleteLeaf(int n, vector<unordered_set<int>>& adjs) {
        vector<int> q;
        for (int i = 0; i < n; ++i) {
            if (adjs[i].size() == 1) {
                q.push_back(i);
            }
        }
        for (auto leaf : q) {
            if (adjs[leaf].empty()) continue;
            int next = *adjs[leaf].begin();
            adjs[leaf].clear();
            adjs[next].erase(leaf);
        }
    }
    int getResult(int n, vector<unordered_set<int>>& adjs) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (!adjs[i].empty()) ++count;
        }
        return count <= 1 ? 0 : (count - 1) * 2;
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
    vector<int> coins = { 1,0,0,0,0,1 };
    vector<vector<int>> edges = { {0,1}, {1,2}, {2,3}, {3,4}, {4,5} };
    Solution s;
    auto actual = s.collectTheCoins(coins, edges);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> coins = { 1,0,0,1,1,0,0,0,0,1,0,0 };
    vector<vector<int>> edges = { {0,1}, {1,2}, {1,3}, {2,4}, {4,5}, {5,6}, {5,7}, {4,8}, {7,9}, {7,10}, {10,11} };
    Solution s;
    auto actual = s.collectTheCoins(coins, edges);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
}

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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount)
    {
        int n = edges.size() + 1;
        vector<vector<int>> adjs(n);
        for (auto &e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        vector<int> parents(n);
        parents[0] = -1;
        stack<int> ps;
        ps.push(0);
        while (!ps.empty()) {
            auto p = ps.top();
            ps.pop();
            for (auto child : adjs[p]) {
                if (child == parents[p]) continue;
                parents[child] = p;
                ps.push(child);
            }
        }

        vector<int> bobs(n, INT_MAX);
        for (int i = 0; bob != -1; ++i, bob = parents[bob]) {
            bobs[bob] = i;
        }
        
        int result = INT_MIN;
        traverse(adjs, parents, amount, bobs, 0, 0, 0, result);
        return result;
    }
    void traverse(vector<vector<int>> &adjs, vector<int> &parents, vector<int> &amount, vector<int> &bobs, int i, int step, int r, int &result)
    {
        if (step < bobs[i]) {
            r += amount[i];
        } else if (step == bobs[i]) {
            r += amount[i] / 2;
        }
        if (i != 0 && adjs[i].size() == 1) {
            result = max(result, r);
            return;
        }
        for (auto child : adjs[i]) {
            if (child == parents[i]) continue;
            traverse(adjs, parents, amount, bobs, child, step + 1, r, result);
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
    vector<vector<int>> edges = {{0, 1}};
    vector<int> amount = { -7280,2350 };
    Solution s;
    auto actual = s.mostProfitablePath(edges, 1, amount);
    decltype(actual) expect = -7280;
    EXPECT_EQ(expect, actual);
    
}

}

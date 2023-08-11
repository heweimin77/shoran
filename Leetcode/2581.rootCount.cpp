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

#include "support.h"

using namespace std;

namespace {

class Solution {
#define MAKE_KEY(x, y) (((unsigned long long)(x) << 32) | (unsigned long long)(y))
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        vector<int> parents(n, -1);
        traverse(adjs, 0, -1, parents);
        int count = 0;
        for (auto& g : guesses) {
            if (parents[g[1]] == g[0]) ++count;
        }

        unordered_set<unsigned long long> gparent;
        for (auto& g : guesses) {
            gparent.insert(MAKE_KEY(g[0], g[1]));
        }
        result = 0;
        traverse2(adjs, 0, -1, count, k, gparent);
        return result;
    }
    void traverse(vector<vector<int>>& adjs, int now, int parent, vector<int>& parents) {
        for (auto next : adjs[now]) {
            if (next == parent) continue;
            parents[next] = now;
            traverse(adjs, next, now, parents);
        }
    }
    void traverse2(vector<vector<int>>& adjs, int now, int parent, int count, int k, unordered_set<unsigned long long>& gparent) {
        if (count >= k) ++result;
        for (auto next : adjs[now]) {
            if (next == parent) continue;
            int ncount = count;
            if (gparent.count(MAKE_KEY(now, next)) > 0) {
                --ncount;
            }
            if (gparent.count(MAKE_KEY(next, now)) > 0) {
                ++ncount;
            }
            traverse2(adjs, next, now, ncount, k, gparent);
        }
    }
private:
    int result;
};

class Solution2Time37 {
public:
    int rootCount(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        int n = edges.size() + 1;
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> parents(n, -1);
            traverse(adjs, i, -1, parents);
            int count = 0;
            for (auto& g : guesses) {
                if (parents[g[1]] == g[0]) ++count;
            }
            if (count >= k) ++result;
        }
        return result;
    }
    void traverse(vector<vector<int>>& adjs, int now, int parent, vector<int>& parents) {
        for (auto next : adjs[now]) {
            if (next == parent) continue;
            parents[next] = now;
            traverse(adjs, next, now, parents);
        }
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
    vector<vector<int>> edges = { {0,1}, {1,2}, {1,3}, {4,2} };
    vector<vector<int>> guesses = { {1,3}, {0,1}, {1,0}, {2,4} };
    Solution s;
    auto actual = s.rootCount(edges, guesses, 3);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

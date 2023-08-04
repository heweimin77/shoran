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
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        if (n == 1) return price[0] / 2;
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }
        vector<vector<unsigned long long>> tripflags(n, vector<unsigned long long>(n));
        vector<int> counts(n);
        for (auto& t : trips) {
            unsigned long long flag = getFlag(tripflags, t[0], t[1], adjs);
            for (int i = 0; i < n; ++i) {
                if (flag & (1ULL << i)) ++counts[i];
            }
        }
        for (int i = 0; i < n; ++i) {
            price[i] *= counts[i];
        }

        queue<int> q;
        vector<int> degree(n);
        for (int i = 0; i < n; ++i) {
            if ((degree[i] = adjs[i].size()) == 1) {
                q.push(i);
            }
        }
        vector<int> results1(n, -1);
        vector<int> results2(n, -1);
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int r1 = price[now], r2 = price[now] / 2;
            int next = -1;
            for (auto nt : adjs[now]) {
                if (results1[nt] < 0) {
                    next = nt;
                } else {
                    r1 += min(results1[nt], results2[nt]);
                    r2 += results1[nt];
                }
            }
            if (next < 0) return min(r1, r2);
            results1[now] = r1;
            results2[now] = r2;
            if (--degree[next] == 1) {
                q.push(next);
            }
        }
        return 0;
    }
    unsigned long long getFlag(vector<vector<unsigned long long>>& tripflags, int source, int dest, vector<vector<int>>& adjs) {
        if (tripflags[source][dest] == 0) {
            queue<int> q;
            q.push(source);
            tripflags[source][source] = 1ULL << source;
            while (!q.empty()) {
                auto now = q.front();
                auto f = tripflags[source][now];
                q.pop();
                for (auto next : adjs[now]) {
                    auto nv = tripflags[source][next];
                    if (nv == 0 || (nv | f) == nv) {
                        tripflags[source][next] = tripflags[next][source] = f | (1ULL << next);
                        q.push(next);
                    }
                }
            }
        }
        return tripflags[source][dest];
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
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
    vector<int> price = { 2,2,10,6 };
    vector<vector<int>> trips = {{0, 3}, {2, 1}, {2, 3}};
    Solution s;
    auto actual = s.minimumTotalPrice(4, edges, price, trips);
    decltype(actual) expect = 23;
    EXPECT_EQ(expect, actual);
}
}

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
    int magnificentSets(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            --e[0], --e[1];
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        vector<int> grpindex(n, -1);
        int grpcount = 0;
        for (int i = 0; i < n; ++i) {
            if (grpindex[i] >= 0) continue;
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                auto now = q.front();
                q.pop();
                grpindex[now] = grpcount;
                for (auto next : adjs[now]) {
                    if (grpindex[next] >= 0) continue;
                    q.push(next);
                }
            }
            ++grpcount;
        }

        vector<int> grpresult(grpcount);
        for (int i = 0; i < n; ++i) {
            int result = 1;
            vector<int> results(n);
            results[i] = 1;
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                auto now = q.front();
                q.pop();
                result = results[now];
                for (auto next : adjs[now]) {
                    if (results[next] == 0) {
                        results[next] = result + 1;
                        q.push(next);
                    } else {
                        if (abs(results[next] - result) != 1) {
                            return -1;
                        }
                    }
                }
            }
            grpresult[grpindex[i]] = max(grpresult[grpindex[i]], result);
        }
        return accumulate(grpresult.begin(), grpresult.end(), 0);
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
    vector<vector<int>> edges = { {1,2}, {1,4}, {1,5}, {2,6}, {2,3}, {4,6} };
    Solution s;
    auto actual = s.magnificentSets(6, edges);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
}


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
    int connectTwoGroups(vector<vector<int>>& cost) {
        int m = cost.size();
        int n = cost[0].size();
        int t = 1 << n;
        vector<vector<int>> adjs(t);
        for (int i = 0; i < t; ++i) {
            for (int k = 1; k < t; ++k) {
                if ((k & i) == 0) {
                    adjs[i].push_back(k);
                }
            }
        }

        vector<int> results(t, INT32_MAX);
        results[0] = 0;

        for (int i = 0; i < m; ++i) {
            auto& cst = cost[i];
            vector<int> connect(t, 0);
            int x = 0;
            for (int k = 1; k < connect.size(); ++k) {
                if (k == (1 << x)) {
                    ++x;
                    connect[k] = cst[x - 1];
                } else {
                    connect[k] = connect[k ^ (1 << (x - 1))] + cst[x - 1];
                }
            }

            vector<int> nexts(t, INT32_MAX);
            nexts[0] = INT32_MAX;
            int xmin = *min_element(cst.begin(), cst.end());
            for (int j = 0; j < results.size(); ++j) {
                if (results[j] == INT32_MAX) continue;
                nexts[j] = min(nexts[j], results[j] + xmin);
                //for (int k = 1; k < connect.size(); ++k) {
                for (auto k : adjs[j]) {
                    auto x = j | k;
                    nexts[x] = min(nexts[x], results[j] + connect[k]);
                }
            }
            results = std::move(nexts);
        }
        return results.back();
    }
};

class Solution2Timeout {
    using Info = pair<int, int>;
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int m = cost.size(), n = cost[0].size();
        unordered_map<int, int> results;
        int s = (1 << (m + n)) - 1;
        results[0] = 0;
        priority_queue<Info, vector<Info>, greater<Info>> q;
        q.push({ 0, 0 });
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.second == s) return now.first;
            for (int i = 0; i < m; ++i) {
                int nt = now.second | (1 << (n + i));
                for (int j = 0; j < n; ++j) {
                    int next = nt | (1 << j);
                    int value = now.first + cost[i][j];
                    auto it = results.find(next);
                    if (it == results.end() || it->second > value) {
                        results[next] = value;
                        q.push({ value, next });
                    }
                }
            }
        }
        return -1;
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
    vector<vector<int>> cost = { {15, 96}, {36, 2} };
    Solution s;
    auto actual = s.connectTwoGroups(cost);
    decltype(actual) expect = 17;
    EXPECT_EQ(expect, actual);
}

}

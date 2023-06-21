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
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        int state = (1 << n) - 1;
        vector<int> results(state + 1);
        queue<int> q;
        q.push(state);
        results[state] = 1;
        while (!q.empty()) {
            int s = q.front();
            if (s == 0) {
                break;
            }
            vector<int> degree(n + 1);
            for (auto& r : relations) {
                if ((s & (1 << (r[0] - 1))) == 0) continue;
                if ((s & (1 << (r[1] - 1))) == 0) continue;
                ++degree[r[1]];
            }
            vector<int> nexts;
            for (int i = 1; i <= n; ++i) {
                if ((s & (1 << (i - 1))) == 0) continue;
                if (degree[i] == 0) {
                    nexts.push_back(i);
                }
            }
            if (nexts.size() <= k) {
                pushq(q, results, s, results[s], nexts);
            } else {
                vector<int> nns(k);
                traverse(nexts, 0, nns, 0, q, results, s, results[s]);
            }

            q.pop();
        }
        return results[0] - 1;
    }
    void traverse(vector<int>& nexts, int nindex, vector<int>& nns, int i, queue<int>& q, vector<int>& results, int s, int r) {
        if (i == nns.size()) {
            pushq(q, results, s, r, nns);
            return;
        }
        for (int x = nindex; x <= nexts.size() + i - nns.size(); ++x) {
            nns[i] = nexts[x];
            traverse(nexts, x + 1, nns, i + 1, q, results, s, r);
        }
    }
    void pushq(queue<int>& q, vector<int>& results, int s, int r, vector<int>& nexts) {
        for (auto n : nexts) {
            s &= ~(1 << (n - 1));
        }
        if (results[s] == 0) {
            results[s] = r + 1;
            q.push(s);
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
    vector<vector<int>> relations = {};
    Solution s;
    auto actual = s.minNumberOfSemesters(4, relations, 2);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

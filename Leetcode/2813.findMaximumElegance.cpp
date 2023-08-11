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
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        unordered_map<int, vector<int>> groups;
        for (auto& i : items) {
            groups[i[1]].push_back(i[0]);
        }
        priority_queue<pair<int, int>> q;
        for (auto& g : groups) {
            sort(g.second.begin(), g.second.end(), greater<int>());
            q.push({ g.second[0], 1 });
            for (int i = 1; i < g.second.size(); ++i) {
                q.push({ g.second[i], 0 });
            }
        }
        int gn = 0;
        stack<int> ss;
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            auto now = q.top();
            q.pop();
            sum += now.first;
            if (now.second == 1) {
                ++gn;
            } else {
                ss.push(now.first);
            }
        }
        int result = sum + gn * gn;
        while (gn < groups.size() && !ss.empty()) {
            sum -= ss.top();
            ss.pop();
            while (!q.empty()) {
                if (q.top().second == 1) {
                    ++gn;
                    sum += q.top().first;
                    result = max(result, sum + gn * gn);
                    q.pop();
                    break;
                }
                q.pop();
            }
        }

        return result;
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
    vector<vector<int>> items = { {3, 2}, {5, 1}, {10, 1} };
    Solution s;
    auto actual = s.findMaximumElegance(items, 2);
    decltype(actual) expect = 17;
    EXPECT_EQ(expect, actual);
}
}

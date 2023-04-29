#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int busRapidTransit(int target, int inc, int dec, vector<int> &jump, vector<int> &cost)
    {
        using Info = pair<long long, long long>;
        priority_queue<Info, vector<Info>, greater<Info>> q;
        q.push({ 0, target });
        unordered_set<int> visited;
        visited.insert(target);
        long long result = target * inc;
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.first >= result) break;
            result = min(result, now.first + now.second * inc);

            for (int i = 0; i < jump.size(); ++i) {
                int x = now.second % jump[i], next = now.second / jump[i];
                if (x == 0) {
                    if (visited.find(next) == visited.end()) {
                        q.push({now.first + cost[i], next});
                    }
                } else {
                    if (visited.find(next) == visited.end()) {
                        q.push({ now.first + cost[i] + x * inc, next});
                    }
                    if (visited.find(next + 1) == visited.end()) {
                        q.push({ now.first + cost[i] + (jump[i] - x) * dec, next + 1});
                    }
                }
            }

        }
        return result % MOD;
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
    vector<int> jump = {6};
    vector<int> cost = {10};
    Solution s;
    auto actual = s.busRapidTransit(31, 5, 3, jump, cost);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

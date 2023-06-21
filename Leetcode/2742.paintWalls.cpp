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
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        map<int, int> results;
        results[n] = (int)(1e9);
        for (int i = 0; i < n; ++i) {
            vector<pair<int, int>> nexts;
            int next = time[i] + 1;
            int value = cost[i];
            nexts.push_back({ next >= n ? n : next, value });
            if (next < n) {
                for (auto& r : results) {
                    auto next = r.first + time[i] + 1;
                    auto value = r.second + cost[i];
                    if (next >= n) {
                        nexts.push_back({ n, value });
                        break;
                    } else {
                        nexts.push_back({ next, value });
                    }
                }
            }
            for (auto& nx : nexts) {
                auto it = results.lower_bound(nx.first);
                if (it->second <= nx.second) continue;
                results[nx.first] = nx.second;
                it = results.lower_bound(nx.first);
                while (it != results.begin()) {
                    --it;
                    if (it->second < nx.second) {
                        break;
                    }
                    it = results.erase(it);
                }
            }
        }
        return results.rbegin()->second;
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
    vector<int> cost = { 1,2,3,2 };
    vector<int> time = { 1,2,3,2 };
    Solution s;
    auto actual = s.paintWalls(cost, time);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
}

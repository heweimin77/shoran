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
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<pair<int, int>>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back({ e[1], e[2] });
            adjs[e[1]].push_back({ e[0], e[2] });
        }

        function<int(int)> getadjs = [&](int i) {
            int result = 0;
            vector<int> distances(n, INT_MAX);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
            distances[i] = 0;
            q.push({ 0, i });
            while (!q.empty()) {
                auto now = q.top();
                q.pop();
                if (now.first > distances[now.second]) continue;
                ++result;
                for (auto next : adjs[now.second]) {
                    int nv = now.first + next.second;
                    if (nv > distanceThreshold) continue;
                    if (nv < distances[next.first]) {
                        distances[next.first] = nv;
                        q.push({ nv, next.first });
                    }
                }
            }
            return result;
        };

        int result = -1;
        int count = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int cnt = getadjs(i);
            if (cnt <= count) {
                count = cnt;
                result = i;
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
    vector<vector<int>> edges = { {0,1,3}, {1,2,1}, {1,3,4}, {2,3,1} };
    Solution s;
    auto actual = s.findTheCity(4, edges, 4);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

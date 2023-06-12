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
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>> &edges, int source, int destination, int target)
    {
        vector<unordered_map<int,int>> adjs(n);
        for (auto &e : edges) {
            adjs[e[0]][e[1]] = e[2];
            adjs[e[1]][e[0]] = e[2];
        }

        vector<int> distances(n, INT_MAX);
        distances[destination] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({ 0, destination });
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.first > distances[now.second]) continue;
            for (auto &next : adjs[now.second]) {
                int nv = next.second == - 1 ? now.first + 1 : now.first + next.second;
                if (distances[next.first] <= nv) continue;
                distances[next.first] = nv;
                q.push({ nv, next.first });
            }
        }
        if (distances[source] > target) return {};

        vector<int> distances2(n, INT_MAX);
        distances2[source] = 0;
        q.push({ 0, source });
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.first > target) return {};
            if (now.first > distances2[now.second]) continue;
            if (now.second == destination) {
                break;
            }
            for (auto &next : adjs[now.second]) {
                if (next.second == -1) {
                    next.second = target - now.first - distances[next.first];
                    if (next.second <= 0) {
                        next.second = 1;
                    }
                    adjs[next.first][now.second] = next.second;
                }                

                int nv = now.first + next.second;
                if (distances2[next.first] <= nv) continue;
                distances2[next.first] = nv;                
                q.push({ nv, next.first });
            }
        }
        if (distances2[destination] != target) return {};
        
        for (auto &e : edges) {
            if (e[2] == -1) {
                e[2] = adjs[e[0]][e[1]];
                if (e[2] == -1) e[2] = 1;
            }
        }
        return edges;
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
    vector<vector<int>> edges = {{4, 1, -1}, {2, 0, -1}, {0, 3, -1}, {4, 3, -1}};
    Solution s;
    auto actual = s.modifiedGraphEdges(5, edges, 0, 1, 5);
    decltype(actual) expect = {{4, 1, 1}, {2, 0, 1}, {0, 3, 3}, {4, 3, 1}};
    EXPECT_EQ_COMPLEX_CONTAINER(expect, actual);
}

}

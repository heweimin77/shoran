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
    int minimumScore(vector<int> &nums, vector<vector<int>> &edges)
    {
        int n = nums.size();
        vector<vector<int>> adjs(n);
        for (auto &e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        vector<unordered_map<int, int>> levelvalues;
        function<int(int, int, int)> getvalues = [&](int now, int parent, int level)->int {
            int r = nums[now];
            for (auto next : adjs[now]) {
                if (next == parent) continue;
                r ^= getvalues(next, now, level + 1);
            }
            if (level >= levelvalues.size()) {
                levelvalues.resize(level + 1);
            }
            levelvalues[level][now] = r;
            return r;
        };
        getvalues(0, -1, 0);

        int total = levelvalues[0][0];
        int result = INT_MAX;
        unordered_set<int> parents;
        function<void(int, int, int)> traverse = [&](int now, int parent, int level) {
            int rs[3] = { 0 };
            for (int i = 1; i <= level; ++i) {
                for (auto r : levelvalues[i]) {
                    if (r.first == now) continue;
                    int other = r.first;
                    if (parents.count(other) > 0) {
                        rs[0] = levelvalues[level][now];
                        rs[1] = rs[0] ^ r.second;
                        rs[2] = total ^ r.second;
                    } else {
                        rs[0] = levelvalues[level][now];
                        rs[1] = r.second;
                        rs[2] = total ^ rs[0] ^ rs[1];
                    }
                    sort(rs, rs + 3);
                    result = min(result, rs[2] - rs[0]);
                }
            }

            parents.insert(now);
            for (auto next : adjs[now]) {
                if (next == parent) continue;
                traverse(next, now, level + 1);
            }
            parents.erase(now);
        };
        traverse(0, -1, 0);

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
    vector<int> nums = { 1,5,5,4,11 };
    vector<vector<int>> edges = { {0,1}, {1,2}, {1,3}, {3,4} };
    Solution s;
    auto actual = s.minimumScore(nums, edges);
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}
}


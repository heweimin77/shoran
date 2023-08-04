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
#define MAKE_POS(x, y) (((unsigned long long)(x) << 32) | (unsigned long long)(y))
#define GET_X(pos) (((pos) >> 32) & 0xFFFFFFFF)
#define GET_Y(pos) ((pos) & 0xFFFFFFFF)

public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        unordered_set<unsigned long long> blockeds;
        for (auto& b : blocked) {
            blockeds.insert(MAKE_POS(b[0], b[1]));
        }

        int limit = blocked.size();
        limit *= limit;
        bool sunlimit = true;
        if (bfs(blockeds, source, target, limit, sunlimit)) {
            return true;
        }
        if (!sunlimit) return false;
        bool tunlimit = true;
        if (bfs(blockeds, target, source, limit, tunlimit)) {
            return true;
        }
        return tunlimit;
    }
    bool bfs(unordered_set<unsigned long long> blockeds, vector<int>& source, vector<int>& target, int limit, bool &isunlimit) {
        unsigned long long tpos = MAKE_POS(target[0], target[1]);
        int umax = 1000000;
        unordered_set<unsigned long long> visited;
        queue<unsigned long long> q;
        visited.insert(MAKE_POS(source[0], source[1]));
        q.push(MAKE_POS(source[0], source[1]));
        int delta[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        while (visited.size() < limit && !q.empty()) {
            unsigned long long now = q.front();
            q.pop();
            int x = GET_X(now);
            int y = GET_Y(now);
            for (auto& d : delta) {
                int nx = x + d[0];
                int ny = y + d[1];
                if (nx < 0 || nx >= umax) continue;
                if (ny < 0 || ny >= umax) continue;
                unsigned long long next = MAKE_POS(nx, ny);
                if (next == tpos) return true;
                if (blockeds.count(next) > 0) continue;
                if (visited.count(next) > 0) continue;
                visited.insert(next);
                q.push(next);
            }
        }
        isunlimit = visited.size() >= limit;
        return false;
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
    vector<vector<int>> blocked = { {0, 1}, {1, 0} };
    vector<int> source = {0, 0};
    vector<int> target = {0, 2};
    Solution s;
    auto actual = s.isEscapePossible(blocked, source, target);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}
}

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
#define MAKE_STATE(e, s, w, n)  ((e) | ((s) << 8) | ((w) << 16) | ((n) << 24))
#define GET_EAST(state)  ((state) & 0xFF)
#define GET_SOUTH(state) (((state) >> 8) & 0xFF)
#define GET_WEST(state) (((state) >> 16) & 0xFF)
#define GET_NORTH(state) (((state) >> 24) & 0xFF)

public:
    int trafficCommand(vector<string>& directions)
    {
        memset(flag, -1, sizeof(flag));

        unordered_map<string, vector<vector<int>>> nextsmap;
        unordered_map<unsigned int, int> results;
        priority_queue<pair<int, unsigned int>, vector<pair<int, unsigned int>>, greater< pair<int, unsigned int>>> q;
        q.push({ 0, MAKE_STATE(directions[0].size(),directions[1].size(),directions[2].size(),directions[3].size()) });
        results[MAKE_STATE(directions[0].size(), directions[1].size(), directions[2].size(), directions[3].size())] = 0;
        while (true) {
            auto now = q.top();
            q.pop();
            if (now.second == 0) return now.first;
            if (results[now.second] < now.first) continue;
            unsigned int dir[4] = { GET_EAST(now.second), GET_SOUTH(now.second), GET_WEST(now.second), GET_NORTH(now.second) };
            string sdir;
            for (int i = 0; i < 4; ++i) {
                if (dir[i] == 0) sdir += ".";
                else sdir += directions[i][dir[i] - 1];
            }

            if (nextsmap.find(sdir) == nextsmap.end()) {
                vector<vector<int>> nexts;
                vector<int> next(4);
                seekNexts(nexts, next, 0, sdir);
                nextsmap[sdir] = nexts;
            }

            for (auto& next : nextsmap[sdir]) {
                auto nstate = MAKE_STATE(dir[0] - next[0], dir[1] - next[1], dir[2] - next[2], dir[3] - next[3]);
                auto v = now.first + 1;
                auto it = results.find(nstate);
                if (it == results.end() || it->second > v) {
                    results[nstate] = v;
                    q.push({ v, nstate });
                }
            }
        }
        return 0;
    }
    void seekNexts(vector<vector<int>>& nexts, vector<int>& next, int i, const string& sdir) {
        if (i == 4) {
            nexts.push_back(next);
            return;
        }
        next[i] = 0;
        seekNexts(nexts, next, i + 1, sdir);
        if (sdir[i] == '.') return;
        for (int j = 0; j < i; ++j) {
            if (next[j] == 0) continue;
            if (!ok(j, getIndex(sdir[j]), i, getIndex(sdir[i]))) {
                return;
            }
        }
        next[i] = 1;
        seekNexts(nexts, next, i + 1, sdir);
    }
    int getIndex(char c) {
        switch (c) {
        case 'E': return 0;
        case 'S': return 1;
        case 'W': return 2;
        default: return 3;
        }
    }
    bool ok(int i, int ic, int j, int jc) {
        if (flag[i][ic][j][jc] < 0) {
            if (ic == jc) {
                flag[i][ic][j][jc] = 0;
            } else {
                int x1 = i + i, x2 = ic + ic + 1;
                if (x1 > x2) swap(x1, x2);
                int y1 = j + j, y2 = jc + jc + 1;
                bool f1 = x1 < y1 && y1 < x2;
                bool f2 = x1 < y2 && y2 < x2;
                flag[i][ic][j][jc] = f1 == f2;

            }
        }
        return flag[i][ic][j][jc];
    }

private:
    int flag[4][4][4][4];
};

class Solution2Timeout {
#define MAKE_STATE(e, s, w, n)  ((e) | ((s) << 8) | ((w) << 16) | ((n) << 24))
#define GET_EAST(state)  ((state) & 0xFF)
#define GET_SOUTH(state) (((state) >> 8) & 0xFF)
#define GET_WEST(state) (((state) >> 16) & 0xFF)
#define GET_NORTH(state) (((state) >> 24) & 0xFF)

public:
    int trafficCommand(vector<string>& directions)
    {
        memset(flag, -1, sizeof(flag));

        unordered_map<unsigned int, int> results;
        priority_queue<pair<int, unsigned int>, vector<pair<int, unsigned int>>, greater< pair<int, unsigned int>>> q;
        q.push({ 0, MAKE_STATE(directions[0].size(),directions[1].size(),directions[2].size(),directions[3].size()) });
        results[MAKE_STATE(directions[0].size(), directions[1].size(), directions[2].size(), directions[3].size())] = 0;
        while (true) {
            auto now = q.top();
            q.pop();
            if (now.second == 0) return now.first;
            if (results[now.second] < now.first) continue;
            unsigned int dir[4] = { GET_EAST(now.second), GET_SOUTH(now.second), GET_WEST(now.second), GET_NORTH(now.second) };
            vector<vector<int>> nexts;
            vector<int> next(4);
            seekNexts(nexts, next, 0, dir, directions);
            for (auto& next : nexts) {
                auto nstate = MAKE_STATE(dir[0] - next[0], dir[1] - next[1], dir[2] - next[2], dir[3] - next[3]);
                auto v = now.first + 1;
                auto it = results.find(nstate);
                if (it == results.end() || it->second > v) {
                    results[nstate] = v;
                    q.push({ v, nstate });
                }
            }
        }
        return 0;
    }
    void seekNexts(vector<vector<int>>& nexts, vector<int>& next, int i, unsigned int dir[], vector<string>& directions) {
        if (i == 4) {
            nexts.push_back(next);
            return;
        }
        next[i] = 0;
        seekNexts(nexts, next, i + 1, dir, directions);
        if (dir[i] == 0) return;
        for (int j = 0; j < i; ++j) {
            if (next[j] == 0) continue;
            if (!ok(j, getIndex(directions[j][dir[j] - 1]), i, getIndex(directions[i][dir[i] - 1]))) {
                return;
            }
        }
        next[i] = 1;
        seekNexts(nexts, next, i + 1, dir, directions);
    }
    int getIndex(char c) {
        switch (c) {
        case 'E': return 0;
        case 'S': return 1;
        case 'W': return 2;
        default: return 3;
        }
    }
    bool ok(int i, int ic, int j, int jc) {
        if (flag[i][ic][j][jc] < 0) {
            if (ic == jc) {
                flag[i][ic][j][jc] = 0;
            } else {
                int x1 = i + i, x2 = ic + ic + 1;
                if (x1 > x2) swap(x1, x2);
                int y1 = j + j, y2 = jc + jc + 1;
                bool f1 = x1 < y1 && y1 < x2;
                bool f2 = x1 < y2 && y2 < x2;
                flag[i][ic][j][jc] = f1 == f2;

            }
        }
        return flag[i][ic][j][jc];
    }

private:
    int flag[4][4][4][4];
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
    vector<string> directions = { "W","N","ES","W" };
    Solution s;
    auto actual = s.trafficCommand(directions);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <stack>
#include <numeric>
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class BlackBox {
public:
    BlackBox(int nn, int mm) : n(nn), m(mm), indexes(m + m + n + n, vector<pair<int, int>>(2, { -1, -1 })) {
        for (int index = 0; index < indexes.size(); ++index) {
            for (int dir = 0; dir < indexes[index].size(); ++dir) {
                if (indexes[index][dir].first >= 0) continue;
                int loopindex = loops.size();
                loops.push_back({});
                auto& loop = loops.back();
                int now = index, dr = dir;
                indexes[now][dr] = { loopindex, loop.size() };
                loop.push_back({ now, dr });
                while (getNext(now, dr, now, dr)) {
                    if (indexes[now][dr].first >= 0) break;
                    indexes[now][dr] = { loopindex, loop.size() };
                    loop.push_back({ now, dr });
                }
            }
        }
        loopstates.resize(loops.size());
    }

    int open(int index, int direction) {
        if (direction == -1) direction = 0;
        for (auto& x : indexes[index]) {
            loopstates[x.first].insert(x.second);
        }

        int loopindex = indexes[index][direction].first;
        int loopindexindex = indexes[index][direction].second;
        auto it = loopstates[loopindex].upper_bound(loopindexindex);
        if (it == loopstates[loopindex].end()) {
            it = loopstates[loopindex].begin();
        }
        return loops[loopindex][*it].first;

    }

    void close(int index) {
        for (auto& x : indexes[index]) {
            loopstates[x.first].erase(x.second);
        }
    }

    bool getNext(int now, int direction, int& next, int &ndir) {
        next = -1;
        int x = now, y = 0;
        if (now > m + m + n) {
            x = 0;
            y = now - (m + m + n + n);
        } else if (now > m + n) {
            x = m + m + n - now;
            y = -n;
        } else if (now > m) {
            x = m;
            y = m - now;
        }
        vector<pair<int, int>> ps;
        if (direction == 1) {
            int dyx = y - x;
            ps.push_back({ 0, dyx });
            ps.push_back({ m, m + dyx });
            ps.push_back({ -dyx,  0 });
            ps.push_back({ -n - dyx,  -n });
        } else {
            int xy = x + y;
            ps.push_back({ 0, xy });
            ps.push_back({ m, xy - m });
            ps.push_back({ xy,  0 });
            ps.push_back({ xy + n,  -n });
        }
        for (auto& p : ps) {
            if (p.first < 0 || p.first > m) continue;
            if (p.second > 0 || p.second < -n) continue;
            if (p.first == x && p.second == y) continue;

            x = p.first, y = p.second;
            if (y == 0) next = x;
            else if (y == -n) next = m + m + n - x;
            else if (x == 0) next = m + m + n + n + y;
            else next = m - y;
            break;
        }
        if (!(next == 0 || next == m || next == n + m || next == m + m + n)) {
            ndir = 1 - direction;
        }
        return next >= 0;
    }

private:
    int n;
    int m;
    vector<vector<pair<int, int>>> loops;
    vector<vector<pair<int, int>>> indexes;
    vector<set<int>> loopstates;
};

class BlackBox2Timeout {
public:
    BlackBox2Timeout(int nn, int mm): n(nn), m(mm), state(nn + nn + mm + mm) {
    }

    int open(int index, int direction) {
        state[index] = true;
        int now = index;
        int next = 0;
        while (getNext(now, direction, next)) {
            if (state[next]) return next;
            now = next;
            direction = -direction;
        }
        if (state[next]) return next;
        return index;
    }

    void close(int index) {
        state[index] = false;
    }
    
    bool getNext(int now, int direction, int& next) {
        int x = now, y = 0;
        if (now > m + m + n) {
            x = 0;
            y = now - (m + m + n + n);
        } else if (now > m + n) {
            x = m + m + n - now;
            y = - n;
        } else if (now > m) {
            x = m;
            y = m - now;
        }
        vector<pair<int,int>> ps;
        if (direction == 1) {
            int dyx = y - x;
            ps.push_back({ 0, dyx });
            ps.push_back({ m, m + dyx });
            ps.push_back({ -dyx,  0});
            ps.push_back({ - n - dyx,  - n});
        } else {
            int xy = x + y;
            ps.push_back({ 0, xy });
            ps.push_back({ m, xy - m});
            ps.push_back({ xy,  0 });
            ps.push_back({ xy + n,  - n });
        }
        for (auto& p : ps) {
            if (p.first < 0 || p.first > m) continue;
            if (p.second > 0 || p.second < -n) continue;
            if (p.first == x && p.second == y) continue;

            x = p.first, y = p.second;
            if (y == 0) next = x;
            else if (y == -n) next = m + m + n - x;
            else if (x == 0) next = m + m + n + n + y;
            else next = m - y;
            break;
        }

        return !(next == 0 || next == m || next == n + m || next == m + m + n);
    }

private:
    int n;
    int m;
    vector<bool> state;
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
    BlackBox box(2, 3);
    EXPECT_EQ(6, box.open(6, -1));
    EXPECT_EQ(4, box.open(4, -1));
    EXPECT_EQ(6, box.open(0, -1));
    box.close(6);
    EXPECT_EQ(4, box.open(0, -1));
}
}


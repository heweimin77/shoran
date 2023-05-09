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
    using Position = long long;
    using Item = pair<int, Position>;
#define MAKE_POS(x, y)  ((((x) & 0xFFFFFFFF) | (((long long)y) << 32)))
#define GET_X(pos) ((pos) & 0xFFFFFFFF)
#define GET_Y(pos)  ((pos) >> 32)
#define DISTANCE(x1, y1, x2, y2) (abs((x1) - (x2)) + abs((y1) - (y2)))
#define PDISTANCE(p1, p2) DISTANCE(GET_X(p1), GET_Y(p1), GET_X(p2), GET_Y(p2))

public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        Position t = MAKE_POS(target[0], target[1]);
        Position s = MAKE_POS(start[0], start[1]);
        
        unordered_map<Position, pair<int, bool>> results;
        unordered_map< Position, vector<Item>> specials;
        for (auto& road : specialRoads) {
            if (DISTANCE(road[0], road[1], road[2], road[3]) <= road[4]) continue;
            Position p1 = MAKE_POS(road[0], road[1]);
            Position p2 = MAKE_POS(road[2], road[3]);
            specials[p1].push_back({ road[4], p2 });
            results[p1] = { PDISTANCE(s, p1), false };
            results[p2] = { PDISTANCE(s, p2), false };
        }
        results[t] = { PDISTANCE(s, t), false };
        results[s] = { 0, false };
        while (true) {
            Position p = 0;
            int v = INT_MAX;
            for (auto& r : results) {
                if (r.second.second) continue;
                if (r.second.first < v) {
                    v = r.second.first;
                    p = r.first;
                }
            }
            if (p == t) return v;
            results[p].second = true;
            for (auto& r : results) {
                if (r.second.second) continue;
                r.second.first = min(r.second.first, (int)PDISTANCE(p, r.first) + v);
            }
            for (auto& spec : specials[p]) {
                auto& next = results[spec.second];
                if (next.second) continue;
                next.first = min(next.first, v + spec.first);
            }
        }
        return 0;
    }
};

class Solution2 {
    using Position = long long;
    using Item = pair<int, Position>;
#define MAKE_POS(x, y)  ((((x) & 0xFFFFFFFF) | (((long long)y) << 32)))
#define GET_X(pos) ((pos) & 0xFFFFFFFF)
#define GET_Y(pos)  ((pos) >> 32)
#define DISTANCE(x1, y1, x2, y2) (abs((x1) - (x2)) + abs((y1) - (y2)))
#define PDISTANCE(p1, p2) DISTANCE(GET_X(p1), GET_Y(p1), GET_X(p2), GET_Y(p2))

public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        list< Position> nexts;
        Position t = MAKE_POS(target[0], target[1]);
        nexts.push_back(t);

        unordered_map<Position, int> results;
        unordered_map< Position, vector<Item>> specials;
        for (auto& road : specialRoads) {
            if (DISTANCE(road[0], road[1], road[2], road[3]) <= road[4]) continue;
            Position p1 = MAKE_POS(road[0], road[1]);
            Position p2 = MAKE_POS(road[2], road[3]);
            nexts.push_back(p1);
            nexts.push_back(p2);
            specials[p1].push_back({ road[4], p2 });
        }

        priority_queue<Item, vector<Item>, std::greater<Item>> q;
        Position s = MAKE_POS(start[0], start[1]);
        results[s] = 0;
        for (auto next : nexts) {
            auto r = results[next] = PDISTANCE(s, next);
            q.push({ r, next });
        }
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            if (now.first > results[now.second]) continue;
            if (now.second == t) {
                return now.first;
            }

            for (auto next : nexts) {
                int dis = now.first + PDISTANCE(now.second, next);
                if (dis < results[next]) {
                    results[next] = dis;
                    q.push({ dis, next });
                }
            }
            for (auto spec : specials[now.second]) {
                auto next = spec.second;
                int dis = now.first + spec.first;
                if (dis < results[next]) {
                    results[next] = dis;
                    q.push({ dis, next });
                }
            }
        }
        return 0;
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

TEST_F(TestSolution, Test1)
{
    vector<int> start = { 1, 1 };
    vector<int> target = { 4, 5 };
    vector<vector<int>> specialRoads = { {3, 2, 3, 4, 4}, {3, 3, 5, 5, 5}, {3, 4, 5, 6, 6} };
    Solution s;
    auto actual = s.minimumCost(start, target, specialRoads);
    decltype(actual) expect = 7;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<int> start  = { 1, 1 };
    vector<int> target = { 10, 4 };
    vector<vector<int>> specialRoads = { {4, 2, 1, 1, 3}, {1, 2, 7, 4, 4}, {10, 3, 6, 1, 2}, {6, 1, 1, 2, 3} };
    Solution s;
    auto actual = s.minimumCost(start, target, specialRoads);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}

}


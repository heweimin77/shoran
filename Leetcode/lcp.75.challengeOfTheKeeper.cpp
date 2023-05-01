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
    using Point = pair<int, int>;
public:
    int challengeOfTheKeeper(vector<string> &maze)
    {
        array<Point, 4> deltas = { { {1, 0}, {-1, 0}, {0, 1}, {0, -1} } };
        Point s, t;
        int m = maze.size(), n = maze[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (maze[i][j] == 'S') s = { i, j };
                else if (maze[i][j] == 'T') t = { i, j };
            }
        }

        vector<vector<unsigned>> distances(m, vector<unsigned>(n, UINT_MAX));
        traverse(maze, t, distances);

        vector<vector<bool>> visited(m, vector<bool>(n));
        priority_queue < pair<unsigned, Point>, vector<pair<unsigned, Point>>, greater< pair<unsigned, Point>>> q;
        unsigned result = 0;
        q.push({ 0, s });
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            result = max(result, now.first);
            if (result == UINT_MAX) break;
            for (auto &d : deltas) {
                Point next = { now.second.first + d.first, now.second.second + d.second };
                if (next.first < 0 || next.first >= m) continue;
                if (next.second < 0 || next.second >= n) continue;
                if (maze[next.first][next.second] == '#') continue;
                if (visited[next.first][next.second]) continue;
                visited[next.first][next.second] = true;
                if (next == t) return result;
                unsigned r = 0;
                if (maze[m - 1 - next.first][next.second] != '#') {
                    r = max(r, distances[m - 1 - next.first][next.second]);
                }
                if (maze[next.first][n - 1 - next.second] != '#') {
                    r = max(r, distances[next.first][n - 1 - next.second]);
                }
                q.push({ r, next });
            }

        }
        
        return -1;
    }
    void traverse(vector<string> &maze, Point &t, vector<vector<unsigned>> &distances)
    {
        int m = maze.size(), n = maze[0].size();
        array<Point, 4> deltas = { { {1, 0}, {-1, 0}, {0, 1}, {0, -1} } };
        queue<Point> q;
        q.push(t);
        distances[t.first][t.second] = 0;
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            auto nv = distances[now.first][now.second] + 1;
            for (auto &delta : deltas) {
                Point next = { now.first + delta.first, now.second + delta.second };
                if (next.first < 0 || next.first >= m) continue;
                if (next.second < 0 || next.second >= n) continue;
                if (maze[next.first][next.second] == '#') continue;
                if (distances[next.first][next.second] != UINT_MAX) continue;
                distances[next.first][next.second] = nv;
                q.push(next);
            }
        }
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
    vector<string> maze = { ".....","##S..","...#.","T.#..","###.." };
    Solution s;
    auto actual = s.challengeOfTheKeeper(maze);
    decltype(actual) expect = 7;
    EXPECT_EQ(expect, actual);
}

}

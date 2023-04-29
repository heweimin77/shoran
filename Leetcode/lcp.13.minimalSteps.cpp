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
    using Point = pair<int, int>;
public:
    int minimalSteps(vector<string> &maze)
    {
        int m = maze.size(), n = maze[0].size();
        Point s, t;
        vector<Point> os, ms;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                switch (maze[i][j]) {
                case 'S': s = { i, j }; break;
                case 'T': t = { i, j }; break;
                case 'M': ms.push_back({ i, j }); break;
                case 'O': os.push_back({ i, j }); break;
                default:
                    break;
                }
            }
        }
        if (ms.empty()) {
            vector<Point> ts = { t };
            vector<unsigned> results;
            getDistance(maze, s, ts, results);
            return results[0];
        }

        int mcount = ms.size();

        vector<unsigned> mts(mcount);
        if (!getDistance(maze, t, ms, mts)) return -1;


        vector<unsigned> sos;
        getDistance(maze, s, os, sos);
        for (int i = sos.size() - 1; i >= 0; --i) {
            if (sos[i] == UINT_MAX) {
                sos.erase(sos.begin() + i);
                os.erase(os.begin() + i);
            }
        }

        vector<vector<unsigned>> mos(mcount);
        for (int i = 0; i < mcount; ++i) {
            getDistance(maze, ms[i], os, mos[i]);
        }
        vector<unsigned> sms(mcount);// s->o->m
        for (int i = 0; i < mcount; ++i) {
            unsigned r = UINT_MAX;
            for (int j = 0; j < os.size(); ++j) {
                if (sos[j] == UINT_MAX || mos[i][j] == UINT_MAX) continue;
                r = min(r, sos[j] + mos[i][j]);
            }
            if (r == UINT_MAX) return -1;
            sms[i] = r;
        }

        vector<vector<unsigned>> mms(mcount, vector<unsigned>(mcount)); // m->o->m
        for (int i = 0; i < mcount; ++i) {
            for (int j = i + 1; j < mcount; ++j) {
                unsigned r = UINT_MAX;
                for (int k = 0; k < os.size(); ++k) {
                    if (mos[i][k] == UINT_MAX || mos[j][k] == UINT_MAX) continue;
                    r = min(r, mos[i][k] + mos[j][k]);
                }
                mms[i][j] = mms[j][i] = r;
            }
        }

        vector<vector<unsigned>> dp(1 << mcount, vector<unsigned>(mcount, UINT_MAX));
        set<pair<int, int>> q;
        for (int i = 0; i < mcount; ++i) {
            dp[1 << i][i] = sms[i];
            q.insert({ 0, i });
        }
        for (unsigned mask = 1; mask < dp.size(); ++mask) {
            for (int i = 0; i < mcount; ++i) {
                if ((mask & (1 << i)) == 0) continue;
                for (int j = 0; j < mcount; ++j) {
                    if (mask & (1 << j)) continue;
                    unsigned nmask = mask | (1 << j);
                    dp[nmask][j] = min(dp[nmask][j], dp[mask][i] + mms[i][j]);
                }
            }
        }
        unsigned result = UINT_MAX;
        auto &rs = dp.back();
        for (int i = 0; i < rs.size(); ++i) {
            result = min(result, rs[i] + mts[i]);
        }
        return result;
    }
    bool getDistance(vector<string> &maze, Point &s, vector<Point> &dst, vector<unsigned> &distance)
    {
        int m = maze.size(), n = maze[0].size();
        vector<vector<unsigned>> results(m, vector<unsigned>(n, UINT_MAX));
        queue<Point> q{ { s } };
        int delta[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        results[s.first][s.second] = 0;
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int nv = results[now.first][now.second] + 1;
            for (auto &d : delta) {
                Point next = { now.first + d[0], now.second + d[1] };
                if (next.first < 0 || next.first >= m) continue;
                if (next.second < 0 || next.second >= n) continue;
                if (maze[next.first][next.second] == '#') continue;
                if (results[next.first][next.second] != UINT_MAX) continue;
                results[next.first][next.second] = nv;
                q.push(next);
            }
        }

        distance.resize(dst.size());
        bool invalid = false;
        for (int i = 0; i < dst.size(); ++i) {
            invalid = (distance[i] = results[dst[i].first][dst[i].second]) == UINT_MAX;
        }
        
        return !invalid;
    }
};

class Solution2Timeout {
    using Point = pair<int, int>;
public:
    int minimalSteps(vector<string> &maze)
    {
        int m = maze.size(), n = maze[0].size();
        Point s, t;
        vector<Point> os, ms;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                switch (maze[i][j]) {
                case 'S': s = { i, j }; break;
                case 'T': t = { i, j }; break;
                case 'M': ms.push_back({ i, j }); break;
                case 'O': os.push_back({ i, j }); break;
                default:
                    break;
                }
            }
        }
        if (ms.empty()) {
            vector<Point> ts = { t };
            vector<unsigned> results;
            getDistance(maze, s, ts, results);
            return results[0];
        }

        int mcount = ms.size();

        vector<unsigned> mts(mcount);
        if (!getDistance(maze, t, ms, mts)) return -1;


        vector<unsigned> sos;
        getDistance(maze, s, os, sos);
        vector<vector<unsigned>> mos(mcount);
        for (int i = 0; i < mcount; ++i) {
            getDistance(maze, ms[i], os, mos[i]);
        }
        vector<unsigned> sms(mcount);// s->o->m
        for (int i = 0; i < mcount; ++i) {
            unsigned r = UINT_MAX;
            for (int j = 0; j < os.size(); ++j) {
                if (sos[j] == UINT_MAX || mos[i][j] == UINT_MAX) continue;
                r = min(r, sos[j] + mos[i][j]);
            }
            if (r == UINT_MAX) return -1;
            sms[i] = r;
        }

        vector<vector<unsigned>> mms(mcount, vector<unsigned>(mcount)); // m->o->m
        for (int i = 0; i < mcount; ++i) {
            for (int j = i + 1; j < mcount; ++j) {
                unsigned r = UINT_MAX;
                for (int k = 0; k < os.size(); ++k) {
                    if (mos[i][k] == UINT_MAX || mos[j][k] == UINT_MAX) continue;
                    r = min(r, mos[i][k] + mos[j][k]);
                }
                mms[i][j] = mms[j][i] = r;
            }
        }

        vector<vector<unsigned>> dp(1 << mcount, vector<unsigned>(mcount, UINT_MAX));
        set<pair<int, int>> q;
        for (int i = 0; i < mcount; ++i) {
            dp[0][i] = sms[i];
            q.insert({ 0, i });
        }
        for (int i = 1; i < mcount; ++i) {
            set<pair<int, int>> nq;
            for (auto &x : q) {
                int mask = x.first | (1 << x.second);
                for (int j = 0; j < mcount; ++j) {
                    if (mask & (1 << j)) continue;
                    dp[mask][j] = min(dp[mask][j], dp[x.first][x.second] + mms[x.second][j]);
                    nq.insert({ mask, j });
                }
            }
            q = std::move(nq);
        }

        unsigned result = UINT_MAX;
        for (auto &x : q) {
            result = min(result, dp[x.first][x.second] + mts[x.second]);
        }
        return result;
    }
    bool getDistance(vector<string> &maze, Point &s, vector<Point> &dst, vector<unsigned> &distance)
    {
        int m = maze.size(), n = maze[0].size();
        vector<vector<unsigned>> results(m, vector<unsigned>(n, UINT_MAX));
        queue<Point> q{ { s } };
        int delta[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        results[s.first][s.second] = 0;
        while (!q.empty()) {
            auto now = q.front();
            q.pop();
            int nv = results[now.first][now.second] + 1;
            for (auto &d : delta) {
                Point next = { now.first + d[0], now.second + d[1] };
                if (next.first < 0 || next.first >= m) continue;
                if (next.second < 0 || next.second >= n) continue;
                if (maze[next.first][next.second] == '#') continue;
                if (results[next.first][next.second] != UINT_MAX) continue;
                results[next.first][next.second] = nv;
                q.push(next);
            }
        }

        distance.resize(dst.size());
        bool invalid = false;
        for (int i = 0; i < dst.size(); ++i) {
            invalid = (distance[i] = results[dst[i].first][dst[i].second]) == UINT_MAX;
        }

        return !invalid;
    }
};

class Solution3Stardard {
public:
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };
    int n, m;

    bool inBound(int x, int y)
    {
        return x >= 0 && x < n &&y >= 0 && y < m;
    }

    vector<vector<int>> bfs(int x, int y, vector<string> &maze)
    {
        vector<vector<int>> ret(n, vector<int>(m, -1));
        ret[x][y] = 0;
        queue<pair<int, int>> Q;
        Q.push({ x, y });
        while (!Q.empty()) {
            auto p = Q.front();
            Q.pop();
            int x = p.first, y = p.second;
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (inBound(nx, ny) && maze[nx][ny] != '#' && ret[nx][ny] == -1) {
                    ret[nx][ny] = ret[x][y] + 1;
                    Q.push({ nx, ny });
                }
            }
        }
        return ret;
    }

    int minimalSteps(vector<string> &maze)
    {
        int t1 = time(nullptr), t2 = 0;
        cout << t1 << endl;
        n = maze.size(), m = maze[0].size();
        // 机关 & 石头
        vector<pair<int, int>> buttons, stones;
        // 起点 & 终点
        int sx, sy, tx, ty;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (maze[i][j] == 'M') {
                    buttons.push_back({ i, j });
                }
                if (maze[i][j] == 'O') {
                    stones.push_back({ i, j });
                }
                if (maze[i][j] == 'S') {
                    sx = i, sy = j;
                }
                if (maze[i][j] == 'T') {
                    tx = i, ty = j;
                }
            }
        }
        int nb = buttons.size();
        int ns = stones.size();
        vector<vector<int>> start_dist = bfs(sx, sy, maze);

        // 边界情况：没有机关
        if (nb == 0) {
            return start_dist[tx][ty];
        }
        // 从某个机关到其他机关 / 起点与终点的最短距离。
        vector<vector<int>> dist(nb, vector<int>(nb + 2, -1));
        // 中间结果
        vector<vector<vector<int>>> dd(nb);
        for (int i = 0; i < nb; i++) {
            vector<vector<int>> d = bfs(buttons[i].first, buttons[i].second, maze);
            dd[i] = d;
            // 从某个点到终点不需要拿石头
            dist[i][nb + 1] = d[tx][ty];
        }

        for (int i = 0; i < nb; i++) {
            int tmp = -1;
            for (int k = 0; k < ns; k++) {
                int mid_x = stones[k].first, mid_y = stones[k].second;
                if (dd[i][mid_x][mid_y] != -1 && start_dist[mid_x][mid_y] != -1) {
                    if (tmp == -1 || tmp > dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y]) {
                        tmp = dd[i][mid_x][mid_y] + start_dist[mid_x][mid_y];
                    }
                }
            }
            dist[i][nb] = tmp;
            for (int j = i + 1; j < nb; j++) {
                int mn = -1;
                for (int k = 0; k < ns; k++) {
                    int mid_x = stones[k].first, mid_y = stones[k].second;
                    if (dd[i][mid_x][mid_y] != -1 && dd[j][mid_x][mid_y] != -1) {
                        if (mn == -1 || mn > dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y]) {
                            mn = dd[i][mid_x][mid_y] + dd[j][mid_x][mid_y];
                        }
                    }
                }
                dist[i][j] = mn;
                dist[j][i] = mn;
            }
        }

        // 无法达成的情形
        for (int i = 0; i < nb; i++) {
            if (dist[i][nb] == -1 || dist[i][nb + 1] == -1) return -1;
        }

        t2 = time(nullptr);
        cout << t2 - t1 << endl;
        t1 = t2;

        // dp 数组， -1 代表没有遍历到
        vector<vector<int>> dp(1 << nb, vector<int>(nb, -1));
        for (int i = 0; i < nb; i++) {
            dp[1 << i][i] = dist[i][nb];
        }

        // 由于更新的状态都比未更新的大，所以直接从小到大遍历即可
        for (int mask = 1; mask < (1 << nb); mask++) {
            for (int i = 0; i < nb; i++) {
                // 当前 dp 是合法的
                if (mask & (1 << i)) {
                    for (int j = 0; j < nb; j++) {
                        // j 不在 mask 里
                        if (!(mask & (1 << j))) {
                            int next = mask | (1 << j);
                            if (dp[next][j] == -1 || dp[next][j] > dp[mask][i] + dist[i][j]) {
                                dp[next][j] = dp[mask][i] + dist[i][j];
                            }
                        }
                    }
                }
            }
        }

        int ret = -1;
        int final_mask = (1 << nb) - 1;
        for (int i = 0; i < nb; i++) {
            if (ret == -1 || ret > dp[final_mask][i] + dist[i][nb + 1]) {
                ret = dp[final_mask][i] + dist[i][nb + 1];
            }
        }
        t2 = time(nullptr);
        cout << t2 - t1 << endl;
        t1 = t2;
        return ret;
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
    //vector<string> maze = { "#...#...#.#...#.##...#......##........#...#.#.#......##......#.#......#.#..", "#.#...#....#.............#.##..#......#........##..#....#...........#......", "..#.......#.##.##..#...#..#...#.#...............#....#..#..##......#.#..#..", ".......#.#........#.....###..#........#...#..##.......#.....#.#............", ".##....#...#....#...##....................#..#.##...##..#.#.#.......#....#.", ".#.#.....#........#...............#....##..#......#...##.#..#...##..#.#.##.", ".#......#.##..#.#..#..........#.........#......####.....#.#.....####...#...", ".......#..........#.##.#..#..................#...#......#.#...#..#.#..##.#.", "..#....#..##.....#.##..........#.......#.......#..............#.##..#.##..#", "......#........##..#.#..#...#.#..##.........#..###.....#.#...#...#..#.####.", ".#...#.........##........###...#..#....#.....#....#....##......##....#...##", "..........#.#........................#...##....#.#.#.............##.#.#..#.", "....#..#.........#.......#..#.......#.##........####....##..##...#..#......", "..##.....#..#....#.........#...###.#.##.#..#.........#..#...##.#........#..", ".#...#...##.#.......................#..#.....#...................#..##...#.", "..........#............#...##............##....#..#.....#....#..#..........", "#....#.#...##..###......T.#.#...##.....#...#.......#.##......#...#..#..#.#.", "......#...............##........##.#.......#.......#.....#.#..#.........##.", ".#...##.....#......#.##.....#......#.#.......#...#...............##.##.....", "#..........#.#.###...#...#......#..##......#....#.......###..M.#.....##....", ".................#....###..#....#.##.#...##......##..................#.....", "................#...#.....#...#..#..#.#....#............#.#..#.......#...#.", "....#..#..........#...#######....#...#...#.....#####..#....#..#..#......#..", "...#.......#.....#....#......#..##..#.............#..#......##...##...#..#.", "........##..#.#.....#...#.....M#...#..#.#..##..##...#...#....#..........#.#", ".#....##...#.#.#.#..#..#.#.#..#...#.#.....#.......#......#..###..#..#.##...", "..#....#.##.......##.....###...#.####.......#......#..#...#.#....#....#.##.", "...#..#..#.....##.......#...........#.....#.#..#...#.#....##...#.##....#...", ".....#...#.#..#..#..#.......#..##...#.....#M.#.......#.....#.#......#.....#", "...#........#.....#...#....#..#..#.#.....##.#...##..........##......#.#..##", "..........#.##.#..###...#..###..##.....#.##....#....#...#..#..#..#...#...#.", "......##........###..#.#.#......#.........#.......#...#...#................", ".#.#......#........##...#................#.##.........####..#..##..#.#.#...", ".##.##.#.........#.....##.#.#......#..##.#..###......##.#..##.#.######...#.", "##.#...#...##.#.#..#......#...............#..................#......#.##..#", ".......#.#.##.#.#.##..#.#..#.##...#...........#...#....#..##.....#....#.#..", "#.............#......#.##....#...#.#..#.............###...............#....", "...##...#..#.........#.#.##.##..##..###.###..#....#........#..##....##.##..", ".#..#.#..#.#....####......#...#............................#.....#....##...", "......#..#...#...#.............#...#.........###........#..#..M....#.......", "..#.##..........#.......##.#......##..#.....#.....#...##......##..........#", "#...#.#.#.....##.#.....#....#...........##........#....#....#..##...#..#.#.", "...##....#...#...........##.#......##.....#.......##..#..........#.........", "..............#.....#..##..#.....#....##.....#.#.............#..###....#.#.", "...##...#....##.#.....#....#...##..#..#.#........##..##.......#...#..###...", "#....#.....#................#.....#.......##................###............", "....##.#....#...............#.......#......#...#...###............##..#.#..", ".###.###...#..#..#.#.............#..#..#.#..........#.....#....#.#.....#...", "#.....##.#......###.#..........#..#.........#...................#....###...", "#.###....##..#...#.#....M.......#.#..........#.........#....#####...#......", ".##.#...............##...#..........#...#..#..........#..##...#.#.#.....#..", ".#......#..#......##........#...#......#.#..#.#.....##.##.#..#....#.##...#.", "...#.#..##.........##.#........#.........#.##..####..##..#..#...#...##...#.", ".#.....#.............##....#..#...#...##..##..##.....##.....#.......#......", "##.#......#...##.........#.###...........#...#.#.......#...#.#..#..##...#..", ".................##.#....#.#..##..................#.##....###......#.......", "..#.#...#......#..###...#.#............#..........#.##..#..#.....#...#.....", ".##....##............#...#.....#.##.....#.#..#.#..##.##......#..........##.", "#.#.......###..####..##..##............##..#...#.#..................#.###.#", "....##.........#.#..#........#..#..##.#......###...#........#.....##..#....", "#...#...#...#.....#.#..#...#.##..................#.##...#.#..#.......#.....", "....#.##.#.###.......#..........#..###.....#....#.#.#.#......#.#..##.#.....", ".#..............##..#.#.........#.#....#S..#.....#.##....#.##...........#..", "..##......#..#.....#.#.#...#.#.....#.#..#####..###...##...#.....#...#.....#", "........#.##..#.##....#......#.##.#......#....#..#.......#.#.....#........#", "......#.....#...##....###.#...#..#..#.......#..#.#....##.#.....#..#.....#..", "..........#.#...#............#....##..###.......#........#..............#..", "..##...#..##.......##......................#.....#.##..#.#...#.....###.#...", "##............##.....#............#.#.....#..##...##..#...#........##......", "#....#....#.........M......#..#..#..#......#......###........#.#........#..", ".#.#..##...#.#...#.#....#.#....#......#.#..#........#............####......", "....#....#....#.#...#....#..#.#....M.....#...........#...#...##.#......#...", "......##...#....#....#..#.#.##.......#....##.#....#..#..#.#...###..##.##...", ".#......#..#.....#.........#....#.............#........##..##....#.....#.#.", ".#.##.##..#..##.##.#....#...#...........#.....#..##................#.##....", "#..#..###......##.##..##.##...............#.........#....##..#...#.#.#....#", "....#.#...##.#.#.......#.#...#....##..............#..##.......##..#..#.....", "...#.#.........##......#.....#..#.##..###..#..#.#........#......##..#.....#", "#.#.....##.##.......#.#.....#......#..##....#....#..#...........#.#..#.....", "...........##...#...#..#....#..##.....#..#...#.##..............#..##.....#.", "......M#.#.#.......##.##....#.#.#........#.##....#........#...###.......#..", "..........###........#......##...#.#...........#....#.##...#.#...#....#....", ".##.....#.......#...#.....#.....#..........#..#....##............#..#..#...", "...........#...#.#.#.#...#.#....#......#........#.#..#...#....#.#..........", ".##...#..#.###..#.........##....#..............#........#.#..#.##M.........", "###....#..#####..#..#..#...#.....#.#......#####.#.........##.#..#....#.#...", "...#..#.......#........#............##.#.#...#.#...#....###..#.............", "..#.#.#....#...#..#..#.#...#......#...###..#..#...#..##..##....#.......#...", "...#......#..##..#..#............###..........#........#...##..##..#....#..", "###........#..##.....#..##......##..#..#.......#..#.....................O..", "........###.#...#......#.......#....#.....#..#..#....##.##..##....#....#.#.", "##..##..##.....##......#....#.#....##.......##.#........##.#..#....####...#", "#..##....#.....##.#.....#.............#...##.#...#...#..#........#.##......", ".##.#.##...........#...........#.......#.##......##..#.......###..#..##...#", "..#........#....##.....#..#......##...##...#.#.#.#......#....#.#..#.....#..", "..#...##.....#.#.#..................#..#.....#..........#..#.M..#........#.", "..#.....##..#.........##...........##....#........#..M...#........#.#......", ".##.##.....#......................#..#.#...#.........#.....#...###....#.#..", "#.##.....#.....#........#.......##..###.........#.#....#.....#..#..##......", "......#.............##......######...#..#.##...#.##.##.....#.#..#.#.#...##." };
    vector<string> maze = { "S#O", "M..", "M.T" };
    Solution s;
    auto actual = s.minimalSteps(maze);
    decltype(actual) expect = 16;// 1416;
    EXPECT_EQ(expect, actual);
}

}

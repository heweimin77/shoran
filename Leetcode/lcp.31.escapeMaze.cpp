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
#define MAKEP(now, x, y, temp, p) ((now << 24) | (x << 16) | (y << 8) | (temp << 4) | (p))
public:
    bool escapeMaze(vector<vector<string>> &maze)
    {
        unordered_set<int> fails;
        int delta[5][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0} };
        int t = maze.size(), m = maze[0].size(), n = maze[0][0].size();

        function<bool(int now, int x, int y, int temp, int p, int px, int py)> dfs = [&](int now, int x, int y, int temp, int p, int px, int py)->bool {
            int flag = MAKEP(now, x, y, temp, p);
            if (fails.count(flag) > 0) return false;

            if (x == m - 1 && y == n - 1) {
                return true;
            }
            if (now + 1 >= t) {
                fails.insert(flag);
                return false;
            }
            for (auto &d : delta) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                if (maze[now + 1][nx][ny] != '#') {
                    if (dfs(now + 1, nx, ny, temp, p, px, py)) {
                        return true;
                    }
                } else {
                    if (nx == px && ny == py) {
                        if (dfs(now + 1, nx, ny, temp, p, px, py)) {
                            return true;
                        }
                    }
                    if (temp == 1) {
                        if (dfs(now + 1, nx, ny, temp - 1, p, px, py)) {
                            return true;
                        }
                    }
                    if (p == 1) {
                        if (dfs(now + 1, nx, ny, temp, p - 1, nx, ny)) {
                            return true;
                        }
                    }
                }
            }
            fails.insert(flag);
            return false;
        };
        return dfs(0, 0, 0, 1, 1, -1, -1);
    }
};


int results[101][51][51][2][2];
class Solution1 {
public:
    bool escapeMaze(vector<vector<string>> &maze)
    {
        int delta[5][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0} };
        int t = maze.size(), m = maze[0].size(), n = maze[0][0].size();
        memset(results, 0, sizeof(results));

        function<bool(int now, int x, int y, int temp, int p, int px, int py)> dfs = [&](int now, int x, int y, int temp, int p, int px, int py)->bool {
            if (results[now][x][y][temp][p] > 0) {
                return results[now][x][y][temp][p] == 1;
            }
            if (x == m - 1 && y == n - 1) {
                results[now][x][y][temp][p] = 1;
                return true;
            }
            if (now + 1 >= t) {
                results[now][x][y][temp][p] = 2;
                return false;
            }
            for (auto &d : delta) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                if (maze[now + 1][nx][ny] != '#') {
                    if (dfs(now + 1, nx, ny, temp, p, px, py)) {
                        results[now][x][y][temp][p] = 1;
                        return true;
                    }
                } else {
                    if (nx == px && ny == py) {
                        if (dfs(now + 1, nx, ny, temp, p, px, py)) {
                            results[now][x][y][temp][p] = 1;
                            return true;
                        }
                    }
                    if (temp == 1) {
                        if (dfs(now + 1, nx, ny, temp - 1, p, px, py)) {
                            results[now][x][y][temp][p] = 1;
                            return true;
                        }
                    }
                    if (p == 1) {
                        if (dfs(now + 1, nx, ny, temp, p - 1, nx, ny)) {
                            results[now][x][y][temp][p] = 1;
                            return true;
                        }
                    }
                }
            }
            results[now][x][y][temp][p] = 2;
            return false;
        };
        return dfs(0, 0, 0, 1, 1, -1, -1);
    }
};

class Solution1Error {
public:
    bool escapeMaze(vector<vector<string>>& maze) {
        union Pos{
            struct { char x; char y; char used; };
            int  value;
        };
        int k = maze.size(), m = maze[0].size(), n = maze[0][0].size();
        unordered_map<int, int> lastindex;
        Pos p;
        p.value = 0;
        p.x = m - 1, p.y = n - 1;
        lastindex[p.value] = k - 1;
        
        int delta2[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        queue<int> q;
        q.push(p.value);
        while (!q.empty()) {
            Pos now;
            now.value = q.front();
            if (now.x == 0 && now.y == 0) return true;
            q.pop();
            int ni = lastindex[now.value] - 1;
            if (ni < 0) continue;
            for (auto& d : delta2) {
                Pos next = now;
                next.x += d[0];
                next.y += d[1];
                if (next.x < 0 || next.x >= m) continue;
                if (next.y < 0 || next.y >= n) continue;
                if (lastindex.count(next.value) > 0) continue;
                auto& mz = maze[ni];
                if (mz[next.x][next.y] == '.') {
                    lastindex[next.value] = ni;
                    q.push(next.value);
                } else {
                    if (next.used == 0) {
                        next.used = 1;
                        lastindex[next.value] = ni;
                        q.push(next.value);
                    }
                }
            }
        }

        int limit = m + n - k;
        unordered_set<long long> nows;
        p.value = 0;
        nows.insert(p.value);
        int delta[][2] = { {0, 0},  {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (int i = 1; i < k; ++i, ++limit) {
            unordered_set<long long> nexts;
            auto& mz = maze[i];
            for (auto now : nows) {
                Pos p, next;
                p.value = now;
                for (auto& d : delta) {
                    next = p;
                    next.x += d[0];
                    next.y += d[1];
                    if (next.x < 0 || next.x >= m) continue;
                    if (next.y < 0 || next.y >= n) continue;
                    if (next.x + next.y < limit) continue;

                    Pos check = next;
                    check.used = 0;
                    auto it = lastindex.find(check.value);
                    if (it != lastindex.end() && i <= it->second) {
                        return true;
                    }
                    if (next.used== 0) {
                        check.used = 1;
                        it = lastindex.find(check.value);
                        if (it != lastindex.end() && i <= it->second) {
                            return true;
                        }
                    }

                    if (mz[next.x][next.y] == '.') {
                        nexts.insert(next.value);
                        continue;
                    }
                    if (next.used == 0) {
                        next.used = 1;
                        nexts.insert(next.value);
                    }
                }
            }
            if (nexts.empty()) return false;
            nows = std::move(nexts);
        }
        return true;
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
    vector<vector<string>> maze = {{".#.", "#.."}, { "...", ".#." }, { ".##", ".#." }, { "..#", ".#." }};
    Solution s;
    auto actual = s.escapeMaze(maze);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<string>> maze = { {"...", "...", "..."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."} };
    Solution s;
    auto actual = s.escapeMaze(maze);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test1)
{
    vector<vector<string>> maze = { {"....###.", "###.#.##", ".##..##."}, {".#####..", "##.####.", "##.####."}, {"....####", "###..###", "##..##.."}, {".####...", "######.#", "###.##.."}, {"..###.##", "########", "#######."}, {"...##.##", "###.####", ".#.#.#.."}, {".######.", "#.#.....", "#.#.#.#."}, {".###.##.", "##.#####", "###.##.."}, {"..#.####", "#####.##", "##.###.."}, {".#.###.#", ".#######", "#####.#."}, {".######.", "####....", ".##..##."}, {".###.#..", "###.#.#.", "#####.#."}, {".###.###", "###.####", "....###."}, {".###.##.", "########", "#####.#."}, {".###.###", "##.####.", ".###...."}, {".#.#.##.", ".##.####", "#####.#."}, {"..#.####", "#.##....", "####...."}, {"..#.##.#", "#.##..#.", "###.###."}, {"..##.#.#", ".##.#..#", ".####..."}, {".##..##.", "########", "#####.#."}, {".####.##", "#.#...##", "#.##..#."}, {"..#.####", "######.#", "###.###."}, {".#..#..#", "###..##.", "#..#...."} };
    Solution s;
    auto actual = s.escapeMaze(maze);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
}

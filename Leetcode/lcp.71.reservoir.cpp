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

using namespace std;

namespace {

    class Solution {
    public:
        int reservoir(vector<string>& shape) {
            int n = shape.size(), m = shape[0].size();
            vector<vector<vector<bool>>> connected(n, vector<vector<bool>>(m, vector<bool>(2, false)));
            vector<vector<vector<bool>>> keep(n, vector<vector<bool>>(m, vector<bool>(2, true)));
            getConnected(shape, n, m, connected);
            getKeep(shape, n, m, keep);
            int result = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        if (connected[i][j][k] && keep[i][j][k]) {
                            //cout << i << ", " << j << ", " << k << endl;
                            ++result;
                        }
                    }
                }
            }
            return result;

        }

        void getConnected(vector<string>& shape, int n, int m, vector<vector<vector<bool>>> &connected) {
            vector<vector<int>> q;
            for (int i = 0; i < n; ++i) {
                q.push_back({ i, 0, 0 });
                q.push_back({ i, m - 1, 1 });
                connected[i][0][0] = true;
                connected[i][m - 1][1] = true;
            }
            for (int j = 0; j < m; ++j) {
                q.push_back({ 0, j,  top(shape[0][j])});
                q.push_back({ n - 1, j, 1 - top(shape[n - 1][j]) });
                connected[0][j][top(shape[0][j])] = true;
                connected[n - 1][j][1 - top(shape[n - 1][j])] = true;
            }
            while (!q.empty()) {
                auto now = q.back();
                q.pop_back();
                vector<vector<int>> nexts;
                char f = shape[now[0]][now[1]];
                if (f == '.') {
                    nexts.push_back({ now[0], now[1], 1 - now[2] });
                }
                if (now[2] == 0) {
                    nexts.push_back({ now[0], now[1] - 1, 1 });
                }
                else {
                    nexts.push_back({ now[0], now[1] + 1, 0 });
                }
                if (now[2] == top(f)) {
                    if (now[0] >= 1) {
                        nexts.push_back({ now[0] - 1, now[1], 1 - top(shape[now[0] - 1][now[1]]) });
                    }
                }
                else {
                    if (now[0] + 1 < n) {
                        nexts.push_back({ now[0] + 1, now[1], top(shape[now[0] + 1][now[1]]) });
                    }
                }
                for (auto& next : nexts) {
                    if (next[0] < 0 || next[0] >= n) continue;
                    if (next[1] < 0 || next[1] >= m) continue;
                    if (connected[next[0]][next[1]][next[2]]) continue;
                    connected[next[0]][next[1]][next[2]] = true;
                    q.push_back(next);
                }
            }
        }
        void getKeep(vector<string>& shape, int n, int m, vector<vector<vector<bool>>> &keep) {
            vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(2, false)));
            for (int i = n - 1; i >= 0; --i) {
                
                vector<vector<int>> q;
                q.push_back({ i, 0, 0 });
                q.push_back({ i, m - 1, 1 });
                visited[i][0][0] = visited[i][m - 1][1] = true;
                for (int j = 0; j < m; ++j) {
                    if (i == n - 1 || visited[i + 1][j][top(shape[i + 1][j])]) {
                        q.push_back({ i, j, 1 - top(shape[i][j]) });
                        visited[i][j][1 - top(shape[i][j])] = true;
                    }
                }
                while (!q.empty()) {
                    auto now = q.back();
                    if (now[0] == i) {
                        keep[now[0]][now[1]][now[2]] = false;
                    }
                    q.pop_back();
                    vector<vector<int>> nexts;
                    char f = shape[now[0]][now[1]];
                    if (f == '.') {
                        nexts.push_back({ now[0], now[1], 1 - now[2] });
                    }
                    if (now[2] == 0) {
                        nexts.push_back({ now[0], now[1] - 1, 1 });
                    }
                    else {
                        nexts.push_back({ now[0], now[1] + 1, 0 });
                    }
                    if (now[2] == top(f)) {
                        if (now[0] >= 1) {
                            nexts.push_back({ now[0] - 1, now[1], 1 - top(shape[now[0] - 1][now[1]]) });
                        }
                    }
                    else {
                        if (now[0] + 1 < n) {
                            nexts.push_back({ now[0] + 1, now[1], top(shape[now[0] + 1][now[1]]) });
                        }
                    }
                    for (auto& next : nexts) {
                        if (next[0] < 0 || next[0] >= n) continue;
                        if (next[1] < 0 || next[1] >= m) continue;
                        if (next[0] < i) continue;
                        if (visited[next[0]][next[1]][next[2]]) continue;
                        visited[next[0]][next[1]][next[2]] = true;
                        q.push_back(next);
                    }
                }
            }
        }
        inline int top(char state) {
            if (state == 'l') return 1;
            else return 0;
        }
    };

    class Solution2 {
    public:
        int reservoir(vector<string>& shape) {
            int n = shape.size(), m = shape[0].size();
            vector<vector<vector<bool>>> connected(n, vector<vector<bool>>(m, vector<bool>(2, false)));
            vector<vector<vector<bool>>> keep(n, vector<vector<bool>>(m, vector<bool>(2, true)));
            getConnected(shape, n, m, connected);
            getKeep(shape, n, m, keep);
            int result = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        if (connected[i][j][k] && keep[i][j][k]) {
                            //cout << i << ", " << j << ", " << k << endl;
                            ++result;
                        }
                    }
                }
            }
            return result;

        }

        void getConnected(vector<string>& shape, int n, int m, vector<vector<vector<bool>>>& connected) {
            vector<vector<int>> q;
            for (int i = 0; i < n; ++i) {
                q.push_back({ i, 0, 0 });
                q.push_back({ i, m - 1, 1 });
                connected[i][0][0] = true;
                connected[i][m - 1][1] = true;
            }
            for (int j = 0; j < m; ++j) {
                q.push_back({ 0, j,  top(shape[0][j]) });
                q.push_back({ n - 1, j, 1 - top(shape[n - 1][j]) });
                connected[0][j][top(shape[0][j])] = true;
                connected[n - 1][j][1 - top(shape[n - 1][j])] = true;
            }
            while (!q.empty()) {
                auto now = q.back();
                q.pop_back();
                vector<vector<int>> nexts;
                char f = shape[now[0]][now[1]];
                if (f == '.') {
                    nexts.push_back({ now[0], now[1], 1 - now[2] });
                }
                if (now[2] == 0) {
                    nexts.push_back({ now[0], now[1] - 1, 1 });
                }
                else {
                    nexts.push_back({ now[0], now[1] + 1, 0 });
                }
                if (now[2] == top(f)) {
                    if (now[0] >= 1) {
                        nexts.push_back({ now[0] - 1, now[1], 1 - top(shape[now[0] - 1][now[1]]) });
                    }
                }
                else {
                    if (now[0] + 1 < n) {
                        nexts.push_back({ now[0] + 1, now[1], top(shape[now[0] + 1][now[1]]) });
                    }
                }
                for (auto& next : nexts) {
                    if (next[0] < 0 || next[0] >= n) continue;
                    if (next[1] < 0 || next[1] >= m) continue;
                    if (connected[next[0]][next[1]][next[2]]) continue;
                    connected[next[0]][next[1]][next[2]] = true;
                    q.push_back(next);
                }
            }
        }
        void getKeep(vector<string>& shape, int n, int m, vector<vector<vector<bool>>>& keep) {
            for (int i = n - 1; i >= 0; --i) {
                vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(2, false)));
                vector<vector<int>> q;

                for (int ii = n - 1; ii >= i; --ii) {
                    q.push_back({ ii, 0, 0 });
                    q.push_back({ ii, m - 1, 1 });
                    visited[ii][0][0] = visited[ii][m - 1][1] = true;
                }
                for (int j = 0; j < m; ++j) {
                    q.push_back({ n - 1, j, 1 - top(shape[n - 1][j]) });
                    visited[n - 1][j][1 - top(shape[n - 1][j])] = true;
                }
                while (!q.empty()) {
                    auto now = q.back();
                    if (now[0] == i) {
                        keep[now[0]][now[1]][now[2]] = false;
                    }
                    q.pop_back();
                    vector<vector<int>> nexts;
                    char f = shape[now[0]][now[1]];
                    if (f == '.') {
                        nexts.push_back({ now[0], now[1], 1 - now[2] });
                    }
                    if (now[2] == 0) {
                        nexts.push_back({ now[0], now[1] - 1, 1 });
                    }
                    else {
                        nexts.push_back({ now[0], now[1] + 1, 0 });
                    }
                    if (now[2] == top(f)) {
                        if (now[0] >= 1) {
                            nexts.push_back({ now[0] - 1, now[1], 1 - top(shape[now[0] - 1][now[1]]) });
                        }
                    }
                    else {
                        if (now[0] + 1 < n) {
                            nexts.push_back({ now[0] + 1, now[1], top(shape[now[0] + 1][now[1]]) });
                        }
                    }
                    for (auto& next : nexts) {
                        if (next[0] < 0 || next[0] >= n) continue;
                        if (next[1] < 0 || next[1] >= m) continue;
                        if (next[0] < i) continue;
                        if (visited[next[0]][next[1]][next[2]]) continue;
                        visited[next[0]][next[1]][next[2]] = true;
                        q.push_back(next);
                    }
                }
            }
        }
        inline int top(char state) {
            if (state == 'l') return 1;
            else return 0;
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
        vector<int> para = { 1,1,1,1 };
        vector<string> spara = { "rlrr","llrl","llr." };
        Solution s;
        auto actual = s.reservoir(spara);
        decltype(actual) expect = 6;
        EXPECT_EQ(expect, actual);
    }
    TEST_F(TestSolution, Test2)
    {
        vector<int> para = { 1,1,1,1 };
        vector<string> spara = { "....rl","l.lr.r",".l..r.","..lr.." };
        Solution s;
        auto actual = s.reservoir(spara);
        decltype(actual) expect = 18;
        EXPECT_EQ(expect, actual);
    }
    TEST_F(TestSolution, Test3)
    {
        vector<int> para = { 1,1,1,1 };
        vector<string> spara = { "rl", "lr" };
        Solution s;
        auto actual = s.reservoir(spara);
        decltype(actual) expect = 0;
        EXPECT_EQ(expect, actual);
    }
}


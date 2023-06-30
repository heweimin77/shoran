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
    bool escapeMaze(vector<vector<string>>& maze) {
        union X{
            char index[4];
            int  value;
        };
        int k = maze.size(), m = maze[0].size(), n = maze[0][0].size();
        unordered_map<int, int> lastindex;
        X x;
        x.value = 0;
        x.index[0] = m - 1, x.index[1] = n - 1;
        lastindex[x.value] = k - 1;
        
        
        int delta2[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        queue<int> q;
        q.push(x.value);
        while (!q.empty()) {
            X now;
            now.value = q.front();
            if (now.index[0] == 0 && now.index[1] == 0) return true;
            q.pop();
            int ni = lastindex[now.value] - 1;
            if (ni < 0) continue;
            for (auto& d : delta2) {
                X next = now;
                next.index[0] += d[0];
                next.index[1] += d[1];
                if (next.index[0] < 0 || next.index[0] >= m) continue;
                if (next.index[1] < 0 || next.index[1] >= n) continue;
                if (lastindex.count(next.value) > 0) continue;
                auto& mz = maze[ni];
                if (mz[next.index[0]][next.index[1]] == '.') {
                    lastindex[next.value] = ni;
                    q.push(next.value);
                } else {
                    if (next.index[2] == 0) {
                        next.index[2] = 1;
                        lastindex[next.value] = ni;
                        q.push(next.value);
                    }
                }
            }
        }

        int limit = m + n - k;
        unordered_set<long long> nows;
        x.value = 0;
        nows.insert(x.value);
        int delta[][2] = { {0, 0},  {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        for (int i = 1; i < k; ++i, ++limit) {
            unordered_set<long long> nexts;
            auto& mz = maze[i];
            for (auto now : nows) {
                union X x, xn;
                x.value = now;
                for (auto& d : delta) {
                    xn = x;
                    xn.index[0] += d[0];
                    xn.index[1] += d[1];
                    if (xn.index[0] < 0 || xn.index[0] >= m) continue;
                    if (xn.index[1] < 0 || xn.index[1] >= n) continue;
                    if (xn.index[0] + xn.index[1] < limit) continue;

                    X xxx = xn;
                    xxx.index[2] = 0;
                    auto it = lastindex.find(xxx.value);
                    if (it != lastindex.end() && i <= it->second) {
                        return true;
                    }
                    if (xn.index[2] == 0) {
                        xxx.index[2] = 1;
                        it = lastindex.find(xxx.value);
                        if (it != lastindex.end() && i <= it->second) {
                            return true;
                        }
                    }

                    if (mz[xn.index[0]][xn.index[1]] == '.') {
                        nexts.insert(xn.value);
                        continue;
                    }
                    if (xn.index[2] == 0) {
                        xn.index[2] = 1;
                        nexts.insert(xn.value);
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

TEST_F(TestSolution, Test1)
{
    vector<vector<string>> maze = {{".#.", "#.."}, { "...", ".#." }, { ".##", ".#." }, { "..#", ".#." }};
    Solution s;
    auto actual = s.escapeMaze(maze);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<string>> maze = { {"...", "...", "..."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."}, {".##", "###", "##."} };
    Solution s;
    auto actual = s.escapeMaze(maze);
    decltype(actual) expect = false;
    EXPECT_EQ(expect, actual);
}
}

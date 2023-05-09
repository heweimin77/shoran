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
#define MAKE_POS(x, y, cnt)  ((x) | ((y) << 8) | ((cnt) << 16))
#define GET_X(pos) ((pos) & 0xFF)
#define GET_Y(pos) (((pos) >> 8) & 0xFF)
#define GET_COUNT(pos) (((pos) >> 16) & 0xFF)
#define DISTANCE(p1, p2) (abs(GET_X(p1) - GET_X(p2)) + abs(GET_Y(p1) - GET_Y(p2)))
public:
    int extractMantra(vector<string>& matrix, string mantra) {
        int m = matrix.size(), n = matrix[0].size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({ 0, 0 });
        unordered_map<int, int> results;
        results[0] = 0;
        int delta[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            int cnt = GET_COUNT(now.second);
            if (cnt == mantra.size()) {
                return now.first + mantra.size();
            }
            if (now.first > results[now.second]) continue;
            int x = GET_X(now.second), y = GET_Y(now.second);
            if (matrix[x][y] == mantra[cnt]) {
                int nextv = now.first;
                int nextp = MAKE_POS(x, y, cnt + 1);
                auto it = results.find(nextp);
                if (it == results.end() || (it->second > nextv)) {
                    results[nextp] = nextv;
                    q.push({ nextv, nextp });
                }
            }

            for (auto &d : delta) {
                int nextx = x + d[0], nexty = y + d[1];
                if (nextx < 0 || nextx >= m) continue;
                if (nexty < 0 || nexty >= n) continue;
                int nextp = MAKE_POS(nextx, nexty, cnt);
                int nextv = now.first + 1;
                auto it = results.find(nextp);
                if (it == results.end() || (it->second > nextv)) {
                    results[nextp] = nextv;
                    q.push({nextv, nextp});
                }
            }
        }

        return -1;
    }
};

class Solution2Timeout {
#define MAKE_POS(x, y)  ((x) | ((y) << 16))
#define GET_X(pos) ((pos) & 0xFFFF)
#define GET_Y(pos) ((pos) >> 16)
#define DISTANCE(p1, p2) (abs(GET_X(p1) - GET_X(p2)) + abs(GET_Y(p1) - GET_Y(p2)))
public:
    int extractMantra(vector<string>& matrix, string mantra) {
        array<vector<int>, 26> mat;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                mat[matrix[i][j] - 'a'].push_back(MAKE_POS(i, j));
            }
        }
        unordered_map<int, int> results = { {0, 0} };
        char last = mantra[0] + 1;
        for (auto ch : mantra) {
            if (ch == last) continue;
            unordered_map<int, int> nexts;
            if (mat[ch - 'a'].empty()) return -1;
            for (int p : mat[ch - 'a']) {
                int rr = INT_MAX;
                for (auto& r : results) {
                    rr = min(rr, r.second + DISTANCE(r.first, p));
                }
                nexts[p] = rr;
            }
            results = std::move(nexts);
        }
        int result = INT_MAX;
        for (auto& r : results) {
            result = min(result, r.second);
        }
        return result + mantra.size();
    }
};

class Solution3Timeout {
#define MAKE_POS(x, y, cnt)  ((x) | ((y) << 8) | ((cnt) << 16))
#define GET_X(pos) ((pos) & 0xFF)
#define GET_Y(pos) (((pos) >> 8) & 0xFF)
#define GET_COUNT(pos) (((pos) >> 16) & 0xFF)
#define DISTANCE(p1, p2) (abs(GET_X(p1) - GET_X(p2)) + abs(GET_Y(p1) - GET_Y(p2)))
public:
    int extractMantra(vector<string>& matrix, string mantra) {
        array<vector<int>, 26> mat;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                mat[matrix[i][j] - 'a'].push_back(MAKE_POS(i, j, 0));
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({ 0, 0 });
        unordered_map<int, int> results;
        results[0] = 0;
        int result = 0;
        while (!q.empty()) {
            auto now = q.top();
            q.pop();
            int cnt = GET_COUNT(now.second);
            if (cnt == mantra.size()) {
                result = now.first;
                break;
            }
            if (now.first > results[now.second]) continue;
            for (auto next : mat[mantra[cnt] - 'a']) {
                int nextv = now.first + DISTANCE(now.second, next);
                int nextp = next | (cnt + 1) << 16;
                auto it = results.find(nextp);
                if (it == results.end() || (it->second > nextv)) {
                    results[nextp] = nextv;
                    q.push({ nextv, nextp });
                }
            }

        }

        return result + mantra.size();
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
    vector<string> matrix = { "sd","ep" };
    string mantra = "speed";
    Solution s;
    auto actual = s.extractMantra(matrix, mantra);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}

}


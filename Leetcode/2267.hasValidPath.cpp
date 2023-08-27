#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
    using Result = vector<pair<int, int>>;
public:
    bool hasValidPath(vector<vector<char>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        if (m + n - 1 & 1) return false;

        vector<vector<Result>> results(m, vector<Result>(n));
        if (grid[0][0] == ')') return false;
        results[0][0] = { { 1, 1 } };
        for (int j = 1; j < n; ++j) {
            auto r = results[0][j - 1][0];
            if (grid[0][j] == '(') ++r.first, ++r.second;
            r.first = max(r.first, j / 2 + 1);
            if (r.first > r.second) break;
            results[0][j] = { r };
        }

        for (int i = 1; i < m; ++i) {
            if (!results[i - 1][0].empty()) {
                auto r = results[i - 1][0][0];
                if (grid[i][0] == '(') ++r.first, ++r.second;
                r.first = max(r.first, i / 2 + 1);
                if (r.first <= r.second)
                    results[i][0] = { r };
            }

            for (int j = 1; j < n; ++j) {
                auto &r1 = results[i][j - 1];
                auto &r2 = results[i - 1][j];
                auto &r = results[i][j];
                if (r1.empty()) r = r2;
                else if (r2.empty()) r = r1;
                else {
                    r.push_back({ min(r1[0].first, r2[0].first), min(r1[0].first, r2[0].first) });
                    int i = 0, j = 0;
                    while (i < r1.size() && j < r2.size()) {
                        auto rr = r2[j];
                        if (r1[i].first < r2[j].first) {
                            rr = r1[i++];
                        } else {
                            ++j;
                        }
                        if (rr.first <= r.back().second + 1) {
                            r.back().second = max(r.back().second, rr.second);
                        } else {
                            r.push_back(rr);
                        }
                    }
                    while (i < r1.size()) {
                        auto rr = r1[i++];
                        if (rr.first <= r.back().second + 1) {
                            r.back().second = max(r.back().second, rr.second);
                        } else {
                            r.push_back(rr);
                        }
                    }
                    while (j < r2.size()) {
                        auto rr = r2[j++];
                        if (rr.first <= r.back().second + 1) {
                            r.back().second = max(r.back().second, rr.second);
                        } else {
                            r.push_back(rr);
                        }
                    }
                }

                if (!r.empty()) {
                    if (grid[i][j] == '(') {
                        for (auto &rr : r) {
                            ++rr.first, ++rr.second;
                        }
                    }
                    int limit = (i + j) / 2 + 1;
                    if (r[0].first < limit) {
                        r[0].first = limit;
                        if (limit > r[0].second) {
                            r.erase(r.begin());
                        }
                    }
                }

            }
        }

        auto &r = results.back().back();
        return !r.empty() && r[0].first == (m + n - 1) / 2;
    }
};

class Solution1Error {
public:
    bool hasValidPath(vector<vector<char>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        if (m + n - 1 & 1) return false;

        vector<vector<pair<int, int>>> results(m, vector<pair<int, int>>(n));
        if (grid[0][0] == ')') return false;
        results[0][0] = { 1, 1 };
        for (int j = 1; j < n; ++j) {
            auto r = results[0][j - 1];
            if (grid[0][j] == '(') ++r.first, ++r.second;
            r.first = max(r.first, j / 2 + 1);
            results[0][j] = r;
        }

        for (int i = 1; i < m; ++i) {
            auto r = results[i - 1][0];
            if (grid[i][0] == '(') ++r.first, ++r.second;
            r.first = max(r.first, i / 2 + 1);
            results[i][0] = r;

            for (int j = 1; j < n; ++j) {
                auto r1 = results[i][j - 1];
                auto r2 = results[i - 1][j];
                pair<int, int> r = { min(r1.first, r2.first), max(r1.second, r2.second) };
                if (r1.first > r1.second) {
                    r = r2;
                } else if (r2.first > r2.second) {
                    r = r1;
                }
                if (grid[i][j] == '(') ++r.first, ++r.second;
                r.first = max(r.first, (i + j) / 2 + 1);
                results[i][j] = r;
            }
        }

        auto &r = results.back().back();
        return r.first <= (m + n - 1) / 2 && r.second >= (m + n - 1) / 2;
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
    vector<vector<char>> grid = { {'(','(','('}, {')','(',')'}, {'(','(',')'}, {'(','(',')'} };
    Solution s;
    auto actual = s.hasValidPath(grid);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}

}


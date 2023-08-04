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
    static constexpr unsigned int xmax = -1;
    class MiniValue {
    public:
        MiniValue() {
            segvalue.push_back({ 0, xmax });
            segvalue.push_back({ INT_MAX, INT_MAX-1 });
        }
        unsigned int getValue(int a) {
            if (segvalue.begin()->first != a) {
                unsigned lastv = xmax;
                while (segvalue.begin()->first <= a) {
                    lastv = segvalue.begin()->second;
                    segvalue.erase(segvalue.begin());
                }
                segvalue.push_front({ a, lastv });
            }
            return segvalue.begin()->second;
        }
        void updateValue(const int a, const int b, const unsigned int v) {
            if (a == b) return;
            if (segvalue.begin()->first != a) {
                unsigned lastv = xmax;
                while (segvalue.begin()->first <= a) {
                    lastv = segvalue.begin()->second;
                    segvalue.erase(segvalue.begin());
                }
                segvalue.push_front({ a, lastv });
            }

            auto next = segvalue.begin();
            auto it = next++;
            for (; next != segvalue.end(); ++it, ++next) {
                if (b == next->first) {
                    it->second = min(v, it->second);
                    break;
                } else if (b < next->first) {
                    segvalue.insert(next, {b, it->second});
                    it->second = min(v, it->second);
                    break;
                } else {
                    it->second = min(v, it->second);
                }
            }

            // merge
            int lastv = INT_MAX;
            for (auto it = segvalue.begin(); it != segvalue.end() && it->second < b; ) {
                if (lastv == it->second) {
                    it = segvalue.erase(it);
                } else {
                    lastv = it->second;
                    ++it;
                }
            }

            //cout << a << ", " << b << ", " << v << ": ";
            //for (auto it = segvalue.begin(); it != segvalue.end(); ++it) {
            //    cout << "(";
            //    cout << it->first << "," << it->second;
            //    cout << ") ";
            //}
            //cout << endl;
        }
    private:
        list<pair<int, unsigned int>> segvalue;
    };

public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<MiniValue> colmins(n);
        colmins[0].updateValue(0, 1, 1);
        unsigned int result = 0;
        for (int i = 0; i < m; ++i) {
            MiniValue line;
            for (int j = 0; j < n; ++j) {
                result = min(line.getValue(j), colmins[j].getValue(i));
                // cout << i << ", " << j << ": " << result << endl;
                int x = grid[i][j];
                if (x == 0 || result == xmax) continue;
                line.updateValue(j + 1, min(j + x + 1, n), result + 1);
                colmins[j].updateValue(i + 1, min(i + x + 1, m), result + 1);
                //cout << i << ", " << j << ": " << result << endl;
            }
        }
        return result;
    }
};

class Solution2OkMap {
    static constexpr unsigned int xmax = -1;
    class MiniValue {
    public:
        MiniValue() {
            segvalue[0] = { INT_MAX, xmax };
        }
        unsigned int getValue(int a) {
            while (segvalue.begin()->second.first <= a) {
                segvalue.erase(segvalue.begin());
            }
            return segvalue.begin()->second.second;
        }
        void updateValue(int a, int b, unsigned int v) {
            if (a == b) return;
            while (segvalue.begin()->second.first <= a) {
                segvalue.erase(segvalue.begin());
            }

            if (a != segvalue.begin()->first) {
                segvalue[a] = segvalue.begin()->second;
                segvalue.erase(segvalue.begin());
            }

            for (auto it = segvalue.begin(); it != segvalue.end(); ++it) {
                if (b == it->second.first) {
                    it->second.second = min(v, it->second.second);
                    break;
                } else if (b < it->second.first) {
                    auto xr = it->second;
                    it->second.first = b;
                    it->second.second = min(v, it->second.second);
                    segvalue[b] = xr;
                    break;
                } else {
                    it->second.second = min(v, it->second.second);
                }
            }

            // merge
            int lastv = INT_MAX;
            for (auto it = segvalue.begin(); it != segvalue.end(); ) {
                if (lastv == it->second.second) {
                    auto jt = it;
                    --jt;
                    jt->second.first = it->second.first;
                    it = segvalue.erase(it);
                } else {
                    lastv = it->second.second;
                    ++it;
                }
            }

        }
    private:
        map<int, pair<int, unsigned int>> segvalue;
    };

public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<MiniValue> colmins(n);
        colmins[0].updateValue(0, 1, 1);
        unsigned int result = 0;
        for (int i = 0; i < m; ++i) {
            MiniValue line;
            for (int j = 0; j < n; ++j) {
                result = min(line.getValue(j), colmins[j].getValue(i));
                // cout << i << ", " << j << ": " << result << endl;
                int x = grid[i][j];
                if (x == 0 || result == xmax) continue;
                line.updateValue(j + 1, min(j + x + 1, n), result + 1);
                colmins[j].updateValue(i + 1, min(i + x + 1, m), result + 1);
            }
        }
        return result;
    }
};

class Solution2Timeout {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<unsigned int>> results(m, vector<unsigned int>(n, -1));
        results[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                unsigned v = results[i][j];
                if (v == -1) continue;
                for (int ii = i + 1; ii <= i + grid[i][j] && ii < m; ++ii) {
                    results[ii][j] = min(results[ii][j], v + 1);
                }
                for (int jj = j + 1; jj <= j + grid[i][j] && jj < n; ++jj) {
                    results[i][jj] = min(results[i][jj], v + 1);
                }
            }
        }
        return results[m - 1][n - 1];
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
    vector<vector<int>> grid = { {3, 4, 2, 1}, {4, 2, 3, 1}, {2, 1, 0, 0}, {2, 4, 0, 0} };
    Solution s;
    auto actual = s.minimumVisitedCells(grid);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<vector<int>> grid = { {0} };
    Solution s;
    auto actual = s.minimumVisitedCells(grid);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<vector<int>> grid = { {2,2,3,4,0} };
    Solution s;
    auto actual = s.minimumVisitedCells(grid);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test4)
{
    vector<vector<int>> grid = { {11, 67, 49, 33, 8, 19, 64, 39, 39, 36, 45, 41, 18, 9, 7, 52, 42, 9, 39, 12, 44, 27, 33, 41, 1}, {37, 15, 43, 1, 53, 57, 13, 11, 6, 10, 6, 49, 8, 41, 18, 54, 0, 6, 12, 26, 40, 14, 26, 35, 27}, {66, 37, 13, 64, 57, 38, 21, 15, 26, 21, 43, 9, 46, 50, 33, 53, 13, 5, 39, 18, 46, 45, 33, 26, 27}, {19, 51, 31, 23, 5, 1, 44, 49, 1, 2, 1, 27, 46, 0, 6, 43, 23, 23, 22, 31, 45, 27, 1, 27, 19}, {36, 30, 30, 36, 28, 20, 4, 57, 56, 36, 51, 19, 8, 28, 28, 16, 38, 26, 43, 0, 7, 21, 40, 36, 27}, {40, 47, 34, 44, 28, 35, 16, 21, 1, 34, 14, 18, 24, 4, 32, 43, 0, 19, 42, 20, 29, 21, 37, 2, 25}, {28, 0, 4, 13, 50, 38, 27, 30, 4, 49, 23, 2, 36, 1, 50, 16, 8, 1, 3, 45, 13, 6, 35, 20, 13}, {55, 2, 26, 17, 43, 38, 0, 32, 28, 20, 53, 24, 13, 25, 34, 33, 29, 32, 24, 41, 40, 15, 22, 30, 22}, {15, 52, 35, 30, 30, 30, 11, 23, 16, 10, 2, 32, 12, 9, 29, 10, 5, 27, 10, 41, 30, 5, 31, 20, 16}, {45, 6, 45, 28, 42, 30, 46, 53, 2, 22, 12, 12, 17, 13, 5, 14, 6, 25, 14, 7, 21, 10, 28, 16, 12}, {37, 6, 33, 11, 44, 35, 18, 14, 41, 51, 5, 21, 43, 7, 18, 9, 5, 25, 3, 1, 28, 33, 25, 17, 2}, {28, 23, 30, 40, 23, 42, 46, 25, 41, 0, 23, 37, 7, 4, 5, 29, 43, 20, 5, 29, 34, 31, 10, 13, 17}, {7, 13, 40, 38, 20, 10, 42, 21, 50, 48, 15, 31, 0, 6, 23, 35, 22, 36, 15, 20, 8, 10, 19, 10, 5}, {18, 31, 28, 11, 28, 16, 8, 49, 0, 28, 29, 35, 4, 30, 25, 17, 5, 11, 6, 26, 16, 28, 2, 25, 13}, {36, 36, 37, 23, 14, 11, 0, 36, 18, 37, 10, 41, 17, 32, 5, 36, 14, 22, 11, 17, 26, 31, 22, 26, 31}, {46, 44, 47, 23, 38, 50, 25, 36, 41, 23, 44, 26, 25, 14, 15, 25, 5, 4, 8, 21, 13, 28, 13, 20, 12}, {44, 9, 1, 15, 13, 29, 25, 0, 36, 41, 5, 37, 29, 37, 0, 12, 24, 17, 0, 34, 31, 11, 16, 31, 25}, {10, 24, 21, 17, 9, 0, 10, 5, 29, 18, 23, 0, 17, 36, 28, 27, 26, 2, 9, 24, 9, 6, 14, 7, 22}, {24, 4, 17, 18, 24, 12, 32, 20, 15, 6, 9, 29, 20, 21, 28, 36, 22, 14, 8, 18, 9, 5, 4, 16, 13}, {42, 36, 15, 41, 46, 15, 30, 38, 7, 25, 32, 31, 3, 30, 8, 1, 35, 3, 27, 27, 11, 10, 21, 8, 4}, {47, 14, 21, 6, 13, 40, 0, 30, 8, 35, 1, 22, 2, 6, 1, 35, 32, 6, 20, 18, 4, 1, 3, 14, 10}, {49, 27, 1, 39, 14, 15, 16, 19, 17, 36, 5, 10, 5, 29, 34, 27, 3, 0, 6, 17, 4, 4, 2, 3, 2}, {12, 33, 30, 35, 11, 19, 13, 21, 0, 37, 36, 12, 0, 27, 17, 21, 11, 6, 21, 21, 19, 17, 20, 2, 16}, {4, 29, 32, 30, 5, 1, 28, 13, 33, 12, 23, 7, 25, 33, 2, 23, 25, 22, 23, 4, 27, 16, 2, 16, 19}, {27, 36, 38, 13, 12, 39, 16, 13, 38, 11, 14, 5, 31, 10, 13, 16, 27, 22, 11, 16, 16, 3, 13, 9, 3}, {9, 11, 13, 13, 23, 17, 14, 8, 13, 18, 17, 14, 19, 17, 8, 21, 12, 14, 12, 10, 3, 19, 18, 21, 6}, {2, 9, 8, 14, 11, 29, 17, 30, 9, 22, 0, 31, 25, 4, 14, 26, 12, 0, 8, 12, 19, 8, 22, 16, 9}, {18, 23, 30, 23, 0, 17, 24, 28, 16, 8, 2, 28, 22, 8, 8, 8, 17, 8, 21, 14, 3, 20, 16, 9, 9}, {23, 25, 24, 35, 8, 30, 0, 28, 28, 28, 18, 3, 5, 3, 11, 25, 16, 23, 5, 11, 6, 14, 13, 17, 5}, {10, 34, 37, 28, 17, 1, 5, 31, 26, 11, 16, 1, 15, 7, 8, 23, 8, 0, 13, 11, 2, 17, 17, 10, 14}, {28, 7, 22, 34, 36, 17, 5, 13, 20, 1, 15, 28, 24, 15, 19, 20, 16, 16, 19, 17, 7, 14, 16, 13, 8}, {19, 5, 25, 5, 22, 26, 16, 15, 3, 13, 2, 13, 6, 22, 3, 11, 13, 5, 2, 19, 7, 9, 7, 13, 2}, {37, 11, 23, 6, 12, 12, 1, 3, 21, 12, 4, 24, 9, 16, 23, 11, 22, 6, 12, 10, 11, 6, 9, 2, 3}, {7, 25, 7, 0, 0, 1, 24, 3, 22, 25, 1, 15, 24, 22, 2, 14, 20, 0, 4, 13, 6, 11, 1, 11, 9}, {36, 27, 18, 5, 2, 27, 26, 15, 17, 26, 2, 24, 19, 18, 0, 9, 17, 12, 13, 1, 11, 4, 4, 8, 1}, {5, 27, 33, 11, 29, 21, 27, 17, 2, 10, 23, 18, 6, 15, 5, 6, 2, 5, 17, 8, 8, 14, 0, 11, 6}, {33, 29, 27, 23, 30, 25, 24, 27, 9, 1, 7, 20, 10, 17, 6, 11, 15, 12, 1, 8, 9, 2, 3, 9, 0}, {6, 14, 9, 12, 3, 18, 26, 2, 21, 1, 4, 6, 17, 17, 17, 8, 4, 13, 4, 4, 4, 0, 10, 5, 3}, {10, 12, 15, 18, 28, 15, 24, 15, 5, 18, 21, 11, 20, 4, 15, 3, 9, 2, 10, 7, 4, 9, 6, 9, 7}, {29, 15, 19, 27, 15, 16, 20, 11, 1, 14, 21, 10, 3, 3, 5, 10, 4, 0, 13, 9, 4, 7, 9, 6, 2}, {26, 18, 21, 13, 23, 10, 24, 11, 18, 6, 8, 19, 3, 15, 1, 15, 6, 5, 5, 6, 3, 0, 8, 5, 3}, {15, 13, 0, 20, 1, 21, 20, 7, 18, 16, 1, 2, 10, 7, 11, 11, 7, 10, 8, 3, 4, 5, 6, 0, 3}, {19, 12, 15, 4, 8, 0, 12, 7, 1, 0, 16, 2, 5, 13, 1, 1, 1, 6, 3, 1, 7, 7, 6, 2, 4}, {22, 20, 16, 0, 5, 5, 9, 9, 19, 13, 3, 11, 6, 8, 8, 11, 0, 8, 5, 6, 0, 5, 1, 3, 2}, {12, 12, 19, 10, 10, 7, 20, 17, 10, 15, 2, 4, 8, 7, 9, 8, 8, 2, 8, 4, 3, 2, 0, 1, 0}, {13, 22, 4, 5, 1, 0, 8, 17, 16, 10, 0, 10, 8, 6, 4, 7, 2, 1, 3, 3, 3, 4, 2, 2, 2}, {11, 15, 7, 5, 7, 10, 6, 12, 2, 10, 8, 1, 3, 4, 3, 8, 3, 7, 6, 3, 2, 1, 1, 0, 0} };
    Solution s;
    auto actual = s.minimumVisitedCells(grid);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}
}

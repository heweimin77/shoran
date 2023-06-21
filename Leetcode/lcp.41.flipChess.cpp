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
    int flipChess(vector<string>& chessboard) {
        int m = chessboard.size(), n = chessboard[0].size();
        return getFlipChess(chessboard, 2, 3);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (chessboard[i][j] == '.') {
                    vector<string> board = chessboard;
                    result = max(result, getFlipChess(board, i, j));
                }
            }
        }
        return result;
    }
    int getFlipChess(vector<string>& chessboard, int i, int j) {
        int m = chessboard.size(), n = chessboard[0].size();
        int deltas[][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
        int result = 0;
        vector<pair<int, int>> changeds;
        chessboard[i][j] = 'X';
        for (auto& d : deltas) {
            pair<int, int> next = { i + d[0], j + d[1] };
            vector<pair<int, int>> whites;
            while (true) {
                if (next.first < 0 || next.first >= m) break;
                if (next.second < 0 || next.second >= n) break;;
                if (chessboard[next.first][next.second] != 'O') break;
                whites.push_back(next);
                next = { next.first + d[0], next.second + d[1] };
            }
            if (whites.empty()) continue;
            if (next.first < 0 || next.first >= m) continue;
            if (next.second < 0 || next.second >= n) continue;;
            if (chessboard[next.first][next.second] != 'X') continue;
            result += whites.size();
            for (auto& w : whites) {
                chessboard[w.first][w.second] = 'X';
                changeds.push_back(w);
            }
        }
        for (auto& w : changeds) {
            result += getFlipChess(chessboard, w.first, w.second);
        }
        return result;
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
    vector<string> chessboard = { "....X.","....X.","XOOO..","......","......" };
    Solution s;
    auto actual = s.flipChess(chessboard);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<string> chessboard = { ".X.",".O.","XO." };
    Solution s;
    auto actual = s.flipChess(chessboard);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<string> chessboard = { ".O.....",".O.....","XOO.OOX",".OO.OO.",".XO.OX.","..X.X.." };
    Solution s;
    auto actual = s.flipChess(chessboard);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
}

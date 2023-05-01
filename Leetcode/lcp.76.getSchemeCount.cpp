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
    static constexpr int BITNUM = 2;
public:
    long long getSchemeCount(int n, int m, vector<string> &chessboard)
    {
        if (m > n) {
            swap(n, m);
            vector<string> other(n, string(m, ' '));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    other[i][j] = chessboard[j][i];
                }
            }
            chessboard = std::move(other);
        }
        unordered_map<unsigned,  long long> statecounts;
        statecounts[0] = 1;
        for (auto &line : chessboard) {
            //printf("line: %s\n", line.c_str());
            unordered_map<unsigned, long long> nexts;
            for (auto &r : statecounts) {
                //printf("now: %x = %d\n", r.first, r.second);
                vector<unsigned> nstates;
                seeknextstate(line, 0, r.first >> 16, nstates, 0, 0);
                for (auto nstate : nstates) {
                    unsigned mask = 0x3;
                    unsigned last2 = r.first >> 16;
                    unsigned last = r.first & 0xFFFF;
                    for (int i = 0; i < m; ++i, mask <<= BITNUM) {
                        if (nstate & mask) {
                            last2 &= ~mask;
                            last2 |= last & mask;
                            last &= ~mask;
                            last |= nstate & mask;
                        }
                    }
                    auto ns = (last2 << 16) | last;
                    nexts[ns] += r.second;
                    //printf("next: %x = %d\n", ns, r.second);
                }
            }
            statecounts = std::move(nexts);
        }
        long long result = 0;
        for (auto &r : statecounts) {
            result += r.second;
        }
        return result;
    }
    void seeknextstate(const string &line, int i, unsigned last2, vector<unsigned> &nstates, unsigned pre, unsigned state) {
        if (i == line.size()) {
            nstates.push_back(state);
            return;
        }
        unsigned flag = ((last2 >> (BITNUM * i)) | (pre >> BITNUM)) & 3;
        switch (line[i]) {
        case '.': 
            seeknextstate(line, i + 1, last2, nstates, pre, state);
            break;
        case 'B':
            if ((flag | 1) != 3) {
                seeknextstate(line, i + 1, last2, nstates, (pre << BITNUM) | 1, state | (1 << BITNUM * i));
            }
            break;
        case 'R':
            if ((flag | 2) != 3) {
                seeknextstate(line, i + 1, last2, nstates, (pre << BITNUM) | 2, state | (2 << BITNUM * i));
            }
            break;
        case '?':
            if ((flag | 1) != 3) {
                seeknextstate(line, i + 1, last2, nstates, (pre << BITNUM) | 1, state | (1 << BITNUM * i));
            }
            if ((flag | 2) != 3) {
                seeknextstate(line, i + 1, last2, nstates, (pre << BITNUM) | 2, state | (2 << BITNUM * i));
            }
            seeknextstate(line, i + 1, last2, nstates, pre, state);
            break;
        }
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
    vector<string> chessboard = { "..R","..B","?R?" };
    Solution s;
    auto actual = s.getSchemeCount(3, 3, chessboard);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test2)
{
    vector<string> chessboard = { "?R?","B?B","?R?" };
    Solution s;
    auto actual = s.getSchemeCount(3, 3, chessboard);
    decltype(actual) expect = 105;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, Test3)
{
    vector<string> chessboard = { "?B","R?","?B" };
    Solution s;
    auto actual = s.getSchemeCount(3, 2, chessboard);
    decltype(actual) expect = 21;
    EXPECT_EQ(expect, actual);
}
}

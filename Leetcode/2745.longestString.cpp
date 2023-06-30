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
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int longestString(int x, int y, int z) {
        if (x == y) {
            return (x + y + z) << 1;
        } else {
            x = min(x, y);
            return (x + x + 1 + z) << 1;
        }
    }
};

class Solution2Timeout {
#define MAKE_STATE(x, y, z, last) ((last) | (z) << 8 | (y) << 16 | (x) << 24)
#define GET_LAST(state)  ((state) & 0xFF)
#define GET_Z(state)  (((state) >> 8) & 0xFF)
#define GET_Y(state)  (((state) >> 16) & 0xFF)
#define GET_X(state) (((state) >> 24) & 0xFF)
public:
    int longestString(int x, int y, int z) {
        vector<vector<int>> adjs = { {1}, {0, 2}, {0, 2} };
        int result = 0;
        unordered_set<int> nows = { MAKE_STATE(x - 1, y, z, 0), MAKE_STATE(x, y - 1, z, 1), MAKE_STATE(x, y, z - 1, 2) };
        while (!nows.empty()) {
            ++result;
            unordered_set<int> nexts;
            for (auto now : nows) {
                vector<int> counts = { GET_X(now), GET_Y(now) , GET_Z(now) };
                int last = GET_LAST(now);
                for (int next : adjs[last]) {
                    if (counts[next] == 0) continue;
                    --counts[next];
                    nexts.insert(MAKE_STATE(counts[0], counts[1], counts[2], next));
                    ++counts[next];
                }
            }
            nows = std::move(nexts);
        }

        return result + result;
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
    Solution s;
    auto actual = s.longestString(2, 5, 1);
    decltype(actual) expect = 12;
    EXPECT_EQ(expect, actual);
}
}

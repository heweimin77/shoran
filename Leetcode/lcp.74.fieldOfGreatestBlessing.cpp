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
public:
    int fieldOfGreatestBlessing(vector<vector<int>> &forceField)
    {
        for (auto &f : forceField) {
            f[0] <<= 1;
            f[1] <<= 1;
        }
        
        map<int, map<int,int>> linecounts;
        for (auto &f : forceField) {
            int x1 = f[0] - f[2], x2 = f[0] + f[2];
            linecounts[x1] = map<int, int>();
        }

        for (auto &f : forceField) {
            int x1 = f[0] - f[2], x2 = f[0] + f[2];
            int y1 = f[1] - f[2], y2 = f[1] + f[2];
            auto it1 = linecounts.lower_bound(x1);
            auto it2 = linecounts.upper_bound(x2);
            for (; it1 != it2; ++it1) {
                ++(it1->second[y1]);
                --(it1->second[y2 + 1]);
            }
        }

        int result = 0;
        for (auto &line : linecounts) {
            int r = 0;
            for (auto &x : line.second) {
                r += x.second;
                result = max(result, r);
            }
        }
        return result;
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
    vector<vector<int>> forceField = { {4, 4, 6}, {7, 5, 3}, {1, 6, 2}, {5, 6, 3} };
    Solution s;
    auto actual = s.fieldOfGreatestBlessing(forceField);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}

}

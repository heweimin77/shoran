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
    double minRecSize(vector<vector<int>> &lines)
    {
        bool init = false;
        double x1, x2;
        double y1, y2;
        for (int i = 0; i < lines.size(); ++i) {
            for (int j = i + 1; j < lines.size(); ++j) {
                if (lines[i][0] == lines[j][0]) continue;
                auto r = getPoint(lines[i][0], lines[i][1], lines[j][0], lines[j][1]);
                if (!init) {
                    init = true;
                    x1 = x2 = r.first;
                    y1 = y2 = r.second;
                }
                x1 = min(x1, r.first);
                x2 = max(x2, r.first);
                y1 = min(y1, r.second);
                y2 = max(y2, r.second);
            }
        }
        return (x2 - x1) * (y2 - y1);
    }
    pair<double, double> getPoint(int k1, int b1, int k2, int b2)
    {
        double x = (b2 - b1) / (k1 - k2);
        double y = k1 * x + b1;
        return { x, y };
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
    vector<vector<int>> lines = {{2, 3}, {3, 0}, {4, 1}};
    Solution s;
    auto actual = s.minRecSize(lines);
    decltype(actual) expect = 48.0;
    EXPECT_EQ(expect, actual);
}
}

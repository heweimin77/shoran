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
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        if (x1 <= xCenter && xCenter <= x2 && y1 <= yCenter && yCenter <= y2) return true;
        int xx = x1 + x2, yy = y1 + y2;
        xx -= xCenter + xCenter;
        yy -= yCenter + yCenter;
        if (xx * xx + yy * yy <= 4 * radius * radius) return true;
        if (checkxline(radius, xCenter, yCenter, x1, y1, y2)) return true;
        if (checkxline(radius, xCenter, yCenter, x2, y1, y2)) return true;
        if (checkyline(radius, xCenter, yCenter, y1, x1, x2)) return true;
        if (checkyline(radius, xCenter, yCenter, y2, x1, x2)) return true;
        return false;
    }
    bool checkxline(int radius, int xCenter, int yCenter, int x, int y1, int y2) {
        double r = radius * radius - (x - xCenter) * (x - xCenter);
        if (r < 0) return false;
        r = sqrt(r);
        return !(yCenter - r > y2 || yCenter + r < y1);
    }
    bool checkyline(int radius, int xCenter, int yCenter, int y, int x1, int x2) {
        double r = radius * radius - (y - yCenter) * (y - yCenter);
        if (r < 0) return false;
        r = sqrt(r);
        return !(xCenter - r > x2 || xCenter + r < x1);
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
    auto actual = s.checkOverlap(1, 0, 0, 1, -1, 3, 1);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}

}

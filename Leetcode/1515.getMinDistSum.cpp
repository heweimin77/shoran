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
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        function<double(double, double)> distance = [&](double x, double y)->double {
            double result = 0.0;
            for (auto p : positions) {
                result += sqrt((x - p[0]) * (x - p[0]) + (y - p[1]) * (y - p[1]));
            }
            return result;
        };
        function<double(double, double)> xdelta = [&](double x, double y)->double {
            double result = 0.0;
            for (auto& p : positions) {
                result += (x - p[0]) / sqrt((x - p[0]) * (x - p[0]) + (y - p[1]) * (y - p[1]));
            }
            return result;
        };
        function<double(double, double)> ydelta = [&](double x, double y)->double {
            double result = 0.0;
            for (auto& p : positions) {
                result += (y- p[1]) / sqrt((x - p[0]) * (x - p[0]) + (y - p[1]) * (y - p[1]));
            }
            return result;
        };

        double x = 0.0, y = 0.0;
        for (auto& p : positions) {
            x += p[0];
            y += p[1];
        }
        x /= positions.size(); 
        y /= positions.size();

        for (double step = 10.0; step >= 1e-5; step /= 10) {
            while (true) {
                double xstep = xdelta(x, y) >= 0 ? -step : step;
                double ystep = ydelta(x, y) >= 0 ? -step : step;
                double nx = x, ny = y;
                double d = distance(x, y);

                double nexts[3][2] = { {x + xstep, y}, {x, y + ystep}, {x + xstep, y + ystep} };
                for (auto& next : nexts) {
                    double dd = distance(next[0], next[1]);
                    if (dd < d) {
                        d = dd;
                        nx = next[0];
                        ny = next[1];
                    }
                }
                if ((x == nx) && (y == ny)) {
                    break;
                }
                x = nx;
                y = ny;
            }
        }
        return distance(x, y);
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
    vector<vector<int>> positions = { {0,1}, {1,0}, {1,2}, {2,1} };
    Solution s;
    auto actual = s.getMinDistSum(positions);
    decltype(actual) expect = 4.0;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> positions = { {1,1}, {0,0}, {2,0} };
    Solution s;
    auto actual = s.getMinDistSum(positions);
    decltype(actual) expect = 2.73205;
    EXPECT_EQ(expect, actual);
}


}

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
    vector<int> visitOrder(vector<vector<int>> &points, string direction)
    {
        int i = min_element(points.begin(), points.end()) - points.begin();
        char pre = 'R';
        pair<int, int> p1 = { points[i][0], points[i][1] };
        pair<int, int> p2 = { points[i][0], points[i][1] - 1};
        vector<bool> visited(points.size());
        visited[i] = true;
        vector<int> results = { i };
        for (auto d : direction) {
            int ii = -1;
            double c = distance(p1.first, p1.second, p2.first, p2.second);
            if (pre == d) {
                double x = 10.0;
                for (int i = 0; i < points.size(); ++i) {
                    if (visited[i]) continue;
                    double b = distance(p2.first, p2.second, points[i][0], points[i][1]);
                    double a = distance(p1.first, p1.second, points[i][0], points[i][1]);
                    double cosx = (a * a + c * c - b * b) / (2.0 * a * c);
                    if (cosx < x) {
                        x = cosx;
                        ii = i;
                    }
                }
            } else {
                double x = -10.0;
                for (int i = 0; i < points.size(); ++i) {
                    if (visited[i]) continue;
                    double b = distance(p2.first, p2.second, points[i][0], points[i][1]);
                    double a = distance(p1.first, p1.second, points[i][0], points[i][1]);
                    double cosx = (a * a + c * c - b * b) / (2.0 * a * c);
                    if (cosx > x) {
                        x = cosx;
                        ii = i;
                    }
                }
            }
            results.push_back(ii);
            visited[ii] = true;
            pre = d;
            p2 = p1;
            p1 = { points[ii][0], points[ii][1] };
        }

        for (int i = 0; i < visited.size(); ++i) {
            if (!visited[i]) {
                visited[i] = true;
                results.push_back(i);
                break;
            }
        }

        return results;
    }
    double distance(int x1, int y1, int x2, int y2)
    {
        x2 -= x1, y2 -= y1;
        return sqrt(x2 * x2 + y2 * y2);
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
    vector<vector<int>> points = {{1, 1}, {1, 2}, {2, 2}, {2, 1}};
    Solution s;
    auto actual = s.visitOrder(points, "RL");
    decltype(actual) expect = { 0,1,3,2 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

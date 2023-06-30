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
    double minRecSize(vector<vector<int>>& lines)
    {
        sort(lines.begin(), lines.end());
        double k = lines[0][0], b1 = lines[0][1], b2 = lines[0][1];
        vector<vector<double>> kbbs;
        for (auto& line : lines) {
            if (k == line[0]) {
                b1 = min(b1, (double)line[1]);
                b2 = max(b2, (double)line[1]);
            } else {
                kbbs.push_back({ k, b1, b2 });
                k = line[0];
                b1 = b2 = line[1];
            }
        }
        kbbs.push_back({ k, b1, b2 });
        if (kbbs.size() <= 1) return 0.0;
        double x2 = (kbbs[1][1] - kbbs[0][2]) / (kbbs[0][0] - kbbs[1][0]);
        double x1 = (kbbs[1][2] - kbbs[0][1]) / (kbbs[0][0] - kbbs[1][0]);
        double y2 = (kbbs[1][1] / kbbs[1][0] - kbbs[0][2] / kbbs[0][0]) / (1.0 / kbbs[1][0] - 1.0 / kbbs[0][0]);
        double y1 = (kbbs[1][2] / kbbs[1][0] - kbbs[0][1] / kbbs[0][0]) / (1.0 / kbbs[1][0] - 1.0 / kbbs[0][0]);
        //cout << x1 << ", " << x2 << ", " << y1 << ", " << y2 << endl;

        for (int i = 2; i < kbbs.size(); ++i) {
            x2 = max(x2, (kbbs[i][1] - kbbs[i - 1][2]) / (kbbs[i - 1][0] - kbbs[i][0]));
            x1 = min(x1, (kbbs[i][2] - kbbs[i - 1][1]) / (kbbs[i - 1][0] - kbbs[i][0]));
            y2 = max(y2, (kbbs[i][1] / kbbs[i][0] - kbbs[i - 1][2] / kbbs[i - 1][0]) / (1.0 / kbbs[i][0] - 1.0 / kbbs[i - 1][0]));
            y1 = min(y1, (kbbs[i][2] / kbbs[i][0] - kbbs[i - 1][1] / kbbs[i - 1][0]) / (1.0 / kbbs[i][0] - 1.0 / kbbs[i - 1][0]));
            //cout << x1 << ", " << x2 << ", " << y1 << ", " << y2 << endl;
        }

        return (x2 - x1) * (y2 - y1);
    }

};


class Solution2Timeout {
public:
    double minRecSize(vector<vector<int>>& lines)
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

TEST_F(TestSolution, Test1)
{
    vector<vector<int>> lines = {{2, 3}, {3, 0}, {4, 1}};
    Solution s;
    auto actual = s.minRecSize(lines);
    decltype(actual) expect = 48.0;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<vector<int>> lines = { {5, 2},{5, -4},{2, -5},{4, -1},{2, 0 }};   
    Solution s;
    auto actual = s.minRecSize(lines);
    decltype(actual) expect = 144;
    EXPECT_EQ(expect, actual);
}
}

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
    bool isPossible(int n, vector<vector<int>> &edges)
    {
        adjs.resize(n);
        for (auto &e : edges) {
            --e[0], --e[1];
            adjs[e[0]].insert(e[1]);
            adjs[e[1]].insert(e[0]);
        }
        vector<int> points;
        for (int i = 0; i < n; ++i) {
            if (adjs[i].size() & 1) points.push_back(i);
        }
        if (points.empty()) return true;
        if (points.size() > 4) return false;
        if (points.size() == 2) return check2(points);
        else return check4(points);
    }
    bool check2(vector<int> &points) {
        int p0 = points[0], p1 = points[1];
        if (check(p0, p1)) return true;
        for (int i = 0; i < adjs.size(); ++i) {
            if (i != p0 && i != p1 && check(i, p0) && check(i, p1)) return true;
        }

        return false;
    }

    bool check4(vector<int> &points) {
        if (check(points[0], points[1]) && check(points[2], points[3])) return true;
        if (check(points[0], points[2]) && check(points[1], points[3])) return true;
        if (check(points[0], points[3]) && check(points[1], points[2])) return true;
        return false;
    }

    bool check(int a, int b)
    {
        if (a == b) return false;
        return adjs[a].count(b) == 0;
    }

private:
    vector<unordered_set<int>> adjs;
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
    vector<vector<int>> edges = { {1,2}, {2,3}, {3,4}, {4,2}, {1,4}, {2,5} };
    Solution s;
    auto actual = s.isPossible(5, edges);
    decltype(actual) expect = true;
    EXPECT_EQ(expect, actual);
}
}


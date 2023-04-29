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
    int closestMeetingNode(vector<int> &edges, int node1, int node2)
    {
        int n = edges.size();
        vector<int> distance1(n, -1), distance2(n, -1);
        for (int i = node1, d = 0; i != -1 && distance1[i] < 0; i = edges[i], ++d) {
            distance1[i] = d;
        }
        for (int i = node2, d = 0; i != -1 && distance2[i] < 0; i = edges[i], ++d) {
            distance2[i] = d;
        }
        int result = -1;
        int md = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (distance1[i] >= 0 && distance2[i] >= 0) {
                int m = max(distance1[i], distance2[i]);
                if (md > m) {
                    md = m;
                    result = i;
                }
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
    vector<int> edges = { 4,4,8,-1,9,8,4,4,1,1 };
    Solution s;
    auto actual = s.closestMeetingNode(edges, 5, 6);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

}


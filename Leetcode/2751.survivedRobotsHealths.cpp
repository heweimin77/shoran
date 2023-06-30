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
#include <stack>
#include <numeric>
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string &directions) {
        int n = positions.size();
        vector<int> indexes(n);
        for (int i = 0; i < n; ++i) indexes[i] = i;
        sort(indexes.begin(), indexes.end(), [&positions](int lhs, int rhs) {
            return positions[lhs] < positions[rhs];
            });
        stack<int> s;
        for (int index : indexes) {
            if (directions[index] == 'R') {
                s.push(index);
            } else {
                int health = healths[index];
                while (!s.empty() && health > 0) {
                    if (healths[s.top()] > health) {
                        --healths[s.top()];
                        health = 0;
                    } else if (healths[s.top()] < health){
                        --health;
                        healths[s.top()] = 0;
                        s.pop();
                    } else {
                        health = healths[s.top()] = 0;
                        s.pop();
                    }
                }
                healths[index] = health;
            }
        }
        healths.erase(remove(healths.begin(), healths.end(), 0), healths.end());
        return healths;
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
    vector<int> positions = { 5,4,3,2,1 };
    vector<int> healths = { 2,17,9,15,10 };
    string directions = "RRRRR";
    Solution s;
    auto actual = s.survivedRobotsHealths(positions, healths, directions);
    decltype(actual) expect = { 2,17,9,15,10 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}

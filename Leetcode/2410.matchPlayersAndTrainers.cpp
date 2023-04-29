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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int matchPlayersAndTrainers(vector<int> &players, vector<int> &trainers)
    {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        trainers.push_back(INT_MAX);
        int result = 0;
        for (int i = 0, j = 0; i < players.size(); ++i,++j) {
            while (trainers[j] < players[i]) ++j;
            if (trainers[j] == INT_MAX) break;
            ++result;
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
    vector<int> players = { 4,7,9 };
    vector<int> trainers = { 8,2,5,8 };
    Solution s;
    auto actual = s.matchPlayersAndTrainers(players, trainers);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}

}

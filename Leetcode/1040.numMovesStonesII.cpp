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
    vector<int> numMovesStonesII(vector<int> &stones)
    {
        sort(stones.begin(), stones.end());
        int r1 = leastMoves(stones);
        int r2 = mostMoves(stones);
        return { r1, r2 };
    }
    int leastMoves(vector<int> &stones)
    {
        int n = stones.size();
        int result = INT_MAX;
        int j = 0;
        for (int i = 0; i < n; ++i) {
            int limit = stones[i] + n - 1;
            while (j < n && stones[j] <= limit) ++j;
            int r = n - j + i;
            if (r == 0) return 0;
            if (r == 1 && stones[j-1] != limit) {
                r = 2;
            }
            result = min(result, r);
        }
        return result;
    }
    int mostMoves(vector<int> &stones)
    {
        int n = stones.size();
        int r = max(stones[n - 2] - stones[0], stones[n - 1] - stones[1]);
        return r + 2 - n;
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
    vector<int> stones = { 4,7,9};
    Solution s;
    auto actual = s.numMovesStonesII(stones);
    decltype(actual) expect = {1, 2};
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


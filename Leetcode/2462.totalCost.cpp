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
    long long totalCost(vector<int> &costs, int k, int candidates)
    {
        int i = candidates, j = costs.size() - candidates - 1;
        if (i > j) {
            j = candidates - 1;
        }
        priority_queue<int, vector<int>, greater<int>> left(costs.begin(), costs.begin() + i), right(costs.begin() + j + 1, costs.end());
        long long result = 0;
        for (; k > 0; --k) {
            if (left.empty()) {
                result += right.top();
                right.pop();
            } else if (right.empty()) {
                result += left.top();
                left.pop();
            } else {
                if (left.top() <= right.top()) {
                    result += left.top();
                    left.pop();
                    if (i <= j) {
                        left.push(costs[i++]);
                    }
                } else {
                    result += right.top();
                    right.pop();
                    if (i <= j) {
                        right.push(costs[j--]);
                    }
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
    vector<int> costs = { 17,12,10,2,7,2,11,20,8 };
    Solution s;
    auto actual = s.totalCost(costs, 3, 4);
    decltype(actual) expect = 11;
    EXPECT_EQ(expect, actual);
    
}

}

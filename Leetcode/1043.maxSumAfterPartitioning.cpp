#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <stack>
#include <time.h>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int maxSumAfterPartitioning(vector<int> &arr, int k)
    {
        vector<int> results(arr.size());
        int i = 0;
        int ma = INT_MIN;
        for (; i < k; ++i) {
            ma = max(ma, arr[i]);
            results[i] = ma * (i + 1);
        }

        for (; i < results.size(); ++i) {
            int r = arr[i] + results[i - 1];
            int ma = arr[i];
            for (int j = i - 1; j > i - k; --j) {
                ma = max(ma, arr[j]);
                r = max(r, ma * (i - j + 1) + results[j - 1]);
            }
            results[i] = r;
        }
        return results.back();
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
    vector<int> arr = { 1,15,7,9,2,5,10 };
    Solution s;
    auto actual = s.maxSumAfterPartitioning(arr, 3);
    decltype(actual) expect = 84;
    EXPECT_EQ(expect, actual);
}

}

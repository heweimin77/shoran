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
    int maximumSum(vector<int>& arr) {
        int result = *max_element(arr.begin(), arr.end());
        if (result <= 0) return result;

        vector<int> rresults(arr.size());
        int r = 0;
        for (int i = arr.size() - 1; i >= 0; --i) {
            r += arr[i];
            if (r < 0) r = 0;
            rresults[i] = r;
        }
        result = rresults[0];

        int lr = 0;
        for (int i = 0; i < arr.size() - 1; ++i) {
            int r = lr + rresults[i + 1];
            result = max(result, r);
            lr += arr[i];
            if (lr < 0) lr = 0;
        }
        lr += arr.back();
        result = max(result, lr);
        return result;
    }
};


class Solution2OK {
public:
    int maximumSum(vector<int>& arr) {
        int result = *max_element(arr.begin(), arr.end());
        int sum = 0, dmin = 0, xsum = 0;
        for (auto n : arr) {
            if (n >= 0) {
                result = max(result, n + sum - dmin);
                sum += n;
                xsum += n;
            } else {
                sum += n;
                dmin = min(dmin, n);
                if (sum <= dmin) {
                    sum = dmin = 0;
                }
                if (xsum > sum - dmin) {
                    sum = xsum + n;
                    dmin = n;
                }
                xsum += n;
                if (xsum < 0) xsum = 0;
            }
        }
        return result;
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
    vector<int> arr = { 11,-10,-11,8,7,-6,9,4,11,6,5,0};
    Solution s;
    auto actual = s.maximumSum(arr);
    decltype(actual) expect = 50;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<int> arr = { 8,-1,6,-7,-4,5,-4,7,-6 };
    Solution s;
    auto actual = s.maximumSum(arr);
    decltype(actual) expect = 17;
    EXPECT_EQ(expect, actual);
}

}

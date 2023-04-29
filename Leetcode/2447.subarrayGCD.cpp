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
    int subarrayGCD(vector<int> &nums, int k)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int gcd = nums[i];
            int j = i;
            for (; j < nums.size(); ++j) {
                if (nums[j] % k != 0) {
                    i = j;
                    break;
                }
                gcd = getgcd(gcd, nums[j]);
                if (gcd == k) break;
            }
            if (gcd == k) {
                for (int x = j; x < nums.size(); ++x) {
                    if (nums[x] % k == 0) ++result;
                    else break;
                }
            }
        }
        return result;
    }
    int getgcd(int a, int b)
    {
        if (a > b) swap(a, b);
        while (a > 0) {
            int x = b % a;
            b = a;
            a = x;
        }
        return b;
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
    vector<int> nums = { 9,3,1,2,6,3 };
    Solution s;
    auto actual = s.subarrayGCD(nums, 3);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}

}

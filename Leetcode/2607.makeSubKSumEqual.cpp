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
    long long makeSubKSumEqual(vector<int> &arr, int k)
    {
        if (k == 1) return makeEqual(arr);
        int n = arr.size();
        long long result = 0;
        vector<int> nums;
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] == 0) continue;
            nums.clear();
            int j = i;
            while (arr[j] != 0) {
                nums.push_back(arr[j]);
                arr[j] = 0;
                j += k;
                if (j >= n) j -= n;
            }
            result += makeEqual(nums);
        }
        return result;
    }
    long long makeEqual(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        auto it = nums.begin() + nums.size() / 2;
        long long result = (long long)(*it) * (it - nums.begin() - (nums.end() - it)) - accumulate(nums.begin(), it, 0LL);
        return accumulate(it, nums.end(), result);
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
    vector<int> arr = { 1,4,1,3 };
    Solution s;
    auto actual = s.makeSubKSumEqual(arr, 2);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}

}


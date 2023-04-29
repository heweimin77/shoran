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
    int makeArrayIncreasing(vector<int> &arr1, vector<int> &arr2)
    {
        constexpr unsigned IMP = -1;
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        arr1.push_back(INT_MAX);
        vector<unsigned> results(arr1.size());
        results[0] = 0;
        for (int i = 1; i < results.size(); ++i) {
            int j = lower_bound(arr2.begin(), arr2.end(), arr1[i]) - arr2.begin();
            unsigned r = i <= j ? i : IMP;
            for (int k = max(0, i - j); k < i; ++k) {
                if (results[k] == IMP) continue;
                if (arr1[k] >= arr1[i]) continue;
                int jk = upper_bound(arr2.begin(), arr2.end(), arr1[k]) - arr2.begin();
                if (i - k - 1 <= j - jk) {
                    r = min(r, results[k] + i - k - 1);
                }
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
    vector<int> arr1 = { 5,16,19,2,1,12,7,14,5,16 };
    vector<int> arr2 = { 6,17,4,3,6,13,4,3,18,17,16,7,14,1,16 };
    Solution s;
    auto actual = s.makeArrayIncreasing(arr1, arr2);
    decltype(actual) expect = 8;
    EXPECT_EQ(expect, actual);
}

}

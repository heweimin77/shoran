#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <string>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<int> addNegabinary(vector<int>& arr1, vector<int>& arr2) {
        if (arr1.size() < arr2.size()) arr1.swap(arr2);
        for (int i = 0, j = arr1.size() - arr2.size(); i < arr2.size(); ++i, ++j) {
            arr1[j] += arr2[i];
        }
        reverse(arr1.begin(), arr1.end());
        int flag = 0;
        for (auto& n : arr1) {
            flag += n;
            if (flag & 1) {
                n = 1;
                --flag;
            } else {
                n = 0;
            }
            flag >>= 1;
            flag = -flag;
        }
        while (flag != 0) {
            if (flag & 1) {
                arr1.push_back(1);
                --flag;
            } else {
                arr1.push_back(0);
            }
            flag >>= 1;
            flag = -flag;
        }

        while (!arr1.empty() && arr1.back() == 0) arr1.pop_back();
        if (arr1.empty()) arr1.push_back(0);
        reverse(arr1.begin(), arr1.end());
        return arr1;
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
    vector<int> arr1 = { 1,1,1,1,1 };
    vector<int> arr2 = { 1,0,1 };
    Solution s;
    auto actual = s.addNegabinary(arr1, arr2);
    decltype(actual) expect = { 1,0,0,0,0 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<int> arr1 = { 0 };
    vector<int> arr2 = { 0 };
    Solution s;
    auto actual = s.addNegabinary(arr1, arr2);
    decltype(actual) expect = { 0 };
    EXPECT_EQ_CONTAINER(expect, actual);
}
}


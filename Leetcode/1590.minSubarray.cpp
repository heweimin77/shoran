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

using namespace std;

namespace {

    class Solution {
    public:
        int minSubarray(vector<int>& nums, int p) {
            long long sum = 0;
            sum = accumulate(nums.begin(), nums.end(), sum);
            sum %= p;
            if (sum == 0) return 0;
            sum = p - sum;

            unordered_map<int, int> indexes;
            indexes[0] = -1;
            int r = INT_MAX;
            int s = 0;
            for (int i = 0; i < nums.size(); ++i) {
                int n = nums[i];
                int d = (s + n + sum) % p;
                auto it = indexes.find(d);
                if (it != indexes.end()) {
                    r = min(r, i - it->second);
                }
                s += n;
                s %= p;
                indexes[s] = i;
            }
            if (r == nums.size()) {
                return -1;
            }
            return r;
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
        vector<int> para = { 6,3,5,2 };
        vector<string> spara = { "hold","engineer","cost","level" };
        Solution s;
        auto actual = s.minSubarray(para, 9);
        decltype(actual) expect = 2;
        EXPECT_EQ(expect, actual);
    }
}


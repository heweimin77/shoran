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

using namespace std;

namespace {

    class Solution {
    public:
        int minimizeSum(vector<int>& nums) {
            if (nums.size() <= 3) return 0;
            int top[3] = { INT_MIN, INT_MIN, INT_MIN };
            int bot[3] = { INT_MAX, INT_MAX, INT_MAX };
            for (auto n : nums) {
                if (n > top[0]) {
                    int i = 0;
                    for (; i < 2 && n > top[i + 1]; ++i) {
                        top[i] = top[i + 1];
                    }
                    top[i] = n;
                }
                if (n < bot[0]) {
                    int i = 0;
                    for (; i < 2 && n < bot[i + 1]; ++i) {
                        bot[i] = bot[i + 1];
                    }
                    bot[i] = n;
                }
            }
            int r = min(top[0] - bot[2], top[1] - bot[1]);
            r = min(r, top[2] - bot[0]);
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
        vector<int> para = { 1,4,7,8,5 };
        Solution s;
        auto actual = s.minimizeSum(para);
        decltype(actual) expect = 3;
        EXPECT_EQ(expect, actual);
    }
}


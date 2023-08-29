#include <string>
#include <array>
#include <vector>
#include "gtest.h"
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <functional>

#include "support.h"

using namespace std;

namespace {

class Solution {
    using ui = unsigned int;
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        ui mask = 0;
        for (int i = 0; i < numSlots; ++i) mask |= (0x2U << i * 2);
        unordered_map<ui, int> results{ { mask, 0 } };

        for (auto n : nums) {
            unordered_map<ui, int> nexts;
            for (auto& r : results) {
                for (int i = 0; i < numSlots; ++i) {
                    int cnt = (r.first >> i * 2) & 0x3;
                    if (cnt == 0) continue;
                    int nmask = r.first - (1 << i * 2);
                    int nvalue = r.second + (n & (i + 1));
                    nexts[nmask] = max(nexts[nmask], nvalue);
                }
            }
            results = std::move(nexts);
        }

        int result = 0;
        for (auto& r : results) {
            result = max(result, r.second);
        }
        return result;
    }
};

class Solution1Timeout76of84 {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int counts[16] = { 0 };
        fill(counts, counts + numSlots + 1, 2);
        int result = 0;
        int data[18];
        int dcnt = 0;
        for (auto n : nums) {
            if (counts[n] > 0) {
                result += n;
                --counts[n];
            } else {
                data[dcnt++] = n;
            }
        }

        function<void(int, int)> traverse = [&](int i, int r) {
            if (i == dcnt) {
                result = max(result, r);
                return;
            }
            for (int j = 1; j <= numSlots; ++j) {
                if (counts[j] == 0) continue;
                --counts[j];
                traverse(i + 1, r + (data[i] & j));
                ++counts[j];
            }
        };
        int r = result;
        traverse(0, r);

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
    vector<int> nums = { 1,2,3,4,5,6 };
    Solution s;
    auto actual = s.maximumANDSum(nums, 3);
    decltype(actual) expect = 9;
    EXPECT_EQ(expect, actual);
}

TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15 };
    Solution s;
    auto actual = s.maximumANDSum(nums, 9);
    decltype(actual) expect = 90;
    EXPECT_EQ(expect, actual);
}
}

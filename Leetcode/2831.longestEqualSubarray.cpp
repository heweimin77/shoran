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
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        unordered_map<int, vector<pair<int, int>>> groups;
        int cnt = 0;
        int num = nums[0];
        for (int i = 0; i < nums.size(); ++i) {
            int n = nums[i];
            if (n == num) {
                ++cnt;
            } else {
                groups[num].push_back({ i - cnt, cnt });
                cnt = 1;
                num = n;
            }
        }
        if (cnt > 0) {
            groups[num].push_back({ nums.size() - cnt, cnt });
        }

        int result = 0;
        for (auto& g : groups) {
            auto& group = g.second;
            int j = 1;
            int delcnt = k;
            int r = group[0].second;
            for (int i = 0; i < group.size(); ++i) {
                for (; j < group.size(); ++j) {
                    if (delcnt - group[j].first + group[j - 1].first + group[j - 1].second < 0) break;
                    r += group[j].second;
                    delcnt -= group[j].first - (group[j - 1].first + group[j - 1].second);
                }
                if (j == group.size()) {
                    result = max(result, r);
                    break;
                }
                result = max(result, r);
                r -= group[i].second;
                delcnt += group[i + 1].first - group[i].first - group[i].second;
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
    vector<int> nums = { 1,3,2,3,1,3 };
    Solution s;
    auto actual = s.longestEqualSubarray(nums, 3);
    decltype(actual) expect = 3;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 1,2,1 };
    Solution s;
    auto actual = s.longestEqualSubarray(nums, 0);
    decltype(actual) expect = 1;
    EXPECT_EQ(expect, actual);
}
}


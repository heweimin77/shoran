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
    int specialPerm(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> adjs(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0) {
                    adjs[i].push_back(j);
                    adjs[j].push_back(i);
                }
            }
        }

        unordered_map<int, unordered_map<int,long long>> results;
        for (int i = 0; i < n; ++i) {
            results[1 << i][i] = 1;
        }
        
        for (int i = 1; i < n; ++i) {
            unordered_map<int, unordered_map<int, long long>> nexts;
            for (auto& now : results) {
                for (auto& r : now.second) {
                    for (auto next : adjs[r.first]) {
                        if ((1 << next) & now.first) continue;
                        nexts[now.first | (1 << next)][next] += r.second;
                    }
                }
            }
            results = std::move(nexts);
            if (results.empty()) return 0;
        }

        long long result = 0;
        for (auto& r : results.begin()->second) {
            result += r.second;
        }
        return result % (int)(1e9 + 7);
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
    vector<int> nums = { 2,3,6 };
    Solution s;
    auto actual = s.specialPerm(nums);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 2,6 };
    Solution s;
    auto actual = s.specialPerm(nums);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

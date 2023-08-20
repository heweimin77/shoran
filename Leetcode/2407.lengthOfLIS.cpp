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
    int lengthOfLIS(vector<int> &nums, int k)
    {
        unordered_map<int, int> results;
        map<int, int> ranges;
        ranges.insert({ 0, 0 });
        ranges.insert({ INT_MAX, INT_MAX });
        for (auto n : nums) {
            auto it = ranges.upper_bound(n);
            --it;
            int v = it->second + 1;
            auto jt = results.find(n);
            if (jt != results.end() && jt->second >= v) continue;
            results[n] = v;

            it = ranges.upper_bound(n + 1);
            --it;
            int lastv = it->second;
            if (it->first == n + 1) {
                it->second = max(it->second, v);
            } else {
                it = ranges.insert({ n + 1, v }).first;
            }
            for (++it; it->first <= n + k; ++it) {
                lastv = it->second;
                it->second = max(it->second, v);
            }
            if (it->first != n + k + 1) {
                ranges.insert({ n + k + 1, lastv });
            }
            
            it = ranges.find(n + 1);
            --it;
            lastv = it->second;
            for (++it; it->second <= n + k + 1; ) {
                if (lastv == it->second) {
                    it = ranges.erase(it);
                } else {
                    lastv = it->second;
                    ++it;
                }
            }

        }
        int result = 0;
        for (auto &r : results) {
            result = max(result, r.second);
        }
        return result;
    }
};

class Solution2Timeout80of84 {
public:
    int lengthOfLIS(vector<int> &nums, int k)
    {
        map<int, int> results;
        for (auto n : nums) {
            auto it = results.lower_bound(n - k);
            auto jt = results.lower_bound(n);
            int r = 0;
            for (; it != jt; ++it) {
                r = max(r, it->second);
            }
            results[n] = max(results[n], r + 1);
        }
        int result = 0;
        for (auto &r : results) {
            result = max(result, r.second);
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

TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 4,2,1,4,3,4,5,8,15 };
    Solution s;
    auto actual = s.lengthOfLIS(nums, 3);
    decltype(actual) expect = 5;
    EXPECT_EQ(expect, actual);
}
}


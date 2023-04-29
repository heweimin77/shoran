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
    int minimizeMax(vector<int> &nums, int p)
    {
        if (p == 0) return 0;
        sort(nums.begin(), nums.end());
        int low = -1, high = nums.back() - nums.front();
        for (int i = 1; i < nums.size(); ++i) {
            nums[i - 1] = nums[i] - nums[i - 1];
        }
        nums.pop_back();
        
        while (low + 1 < high) {
            int mid = (low + high) / 2;
            int cnt = 0;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] <= mid) {
                    if (++cnt >= p) break;
                    ++i;
                }
            }
            if (cnt == p) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high;
    }
};


class Solution2Slow {
public:
    int minimizeMax(vector<int> &nums, int p)
    {
        if (p == 0) return 0;
        sort(nums.begin(), nums.end());
        vector<int> r1(p + 1, INT_MAX), r2(p + 1, INT_MAX), now(p + 1, INT_MAX);
        r1[0] = r2[0] = now[0] = 0;
        r1[1] = nums[1] - nums[0];
        for (int i = 2; i < nums.size(); ++i) {
            for (int j = 1; j <= p; ++j) {
                int r = r1[j];
                int rr = max(r2[j - 1], nums[i] - nums[i - 1]);
                r = min(r, rr);
                if (r == INT_MAX) break;
                now[j] = r;
            }
            r2.swap(r1);
            r1.swap(now);
        }
        return r1[p];
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
    vector<int> nums = { 0,5,3,4 };
    Solution s;
    auto actual = s.minimizeMax(nums, 0);
    decltype(actual) expect = 0;
    EXPECT_EQ(expect, actual);
}

}


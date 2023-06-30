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
#include <iomanip>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        k = nums.size() / k;
        sort(nums.begin(), nums.end());
        unordered_map<int, int> results;
        unordered_set<int> nows;
        int x = (1 << nums.size()) - 1;
        results[x] = 0;
        nows.insert(x);
        while (!nows.empty()) {
            unordered_set<int> nexts;
            for (auto n : nows) {
                if (n == 0) {
                    return results[0];
                }
                int v = results[n];
                int xmin = INT_MAX;
                int xmax = INT_MIN;
                traverse(n, v, 0, nums, 0, k, xmin, xmax, results, nexts);
            }
            nows = std::move(nexts);
        }
        return -1;
    }
    void traverse(int now, int v, int next, vector<int>& nums, int i, int k, int xmin, int xmax, unordered_map<int, int>& results, unordered_set<int>& nexts) {
        if (k == 0) {
            next = now & (~next);
            v += xmax - xmin;
            nexts.insert(next);
            auto it = results.find(next);
            if (it == results.end()) {
                results.insert({ next, v});
            } else {
                it->second = min(it->second, v);
            }
            //cout << std::hex << now << ": " << std::dec << v - xmax + xmin << "; " << std::hex << next << ": " << std::dec << v << endl;
            return;
        }
        for (; i < nums.size(); ++i) {
            int mask = 1 << i;
            if ((now & mask) == 0) continue;
            if (xmax == nums[i]) continue;
            traverse(now, v, next | mask, nums, i + 1, k - 1, min(xmin, nums[i]), nums[i], results, nexts);
        }
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
    vector<int> nums = { 1,2,1,4 };
    Solution s;
    auto actual = s.minimumIncompatibility(nums, 2);
    decltype(actual) expect = 4;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = {1, 1, 2, 2, 3, 3, 6, 8};
    Solution s;
    auto actual = s.minimumIncompatibility(nums, 4);
    decltype(actual) expect = 6;
    EXPECT_EQ(expect, actual);
}
}

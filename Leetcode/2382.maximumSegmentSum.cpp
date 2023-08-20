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
    vector<long long> maximumSegmentSum(vector<int> &nums, vector<int> &removeQueries)
    {
        int n = nums.size();
        vector<long long> sums;
        long long s = 0;
        for (auto n : nums) {
            s += n;
            sums.push_back(s);
        }
        map<int, int> ranges;
        ranges[0] = n - 1;
        priority_queue<pair<long long, pair<int, int>>> q;
        q.push({ sums[n - 1], {0, n - 1} });
        vector<long long> results;
        for (auto r : removeQueries) {
            auto it = ranges.upper_bound(r);
            --it;
            auto range = *it;
            if (it->first == it->second) {
                ranges.erase(it);
            } else if (r == it->first) {
                ranges.erase(it);
                ranges.insert({ range.first + 1, range.second });
                q.push({ sums[range.second] - sums[range.first], {range.first + 1, range.second} });
            } else if (r == it->second) {
                it->second -= 1;
                q.push({ it->first == 0 ? sums[it->second] : sums[it->second] - sums[it->first - 1], {it->first, it->second} });
            } else {
                it->second = r - 1;
                q.push({ it->first == 0 ? sums[it->second] : sums[it->second] - sums[it->first - 1], {it->first, it->second} });
                ranges.insert({ r + 1, range.second });
                q.push({ sums[range.second] - sums[r], {r + 1, range.second} });
            }

            while (!q.empty()) {
                auto now = q.top();
                auto it = ranges.find(now.second.first);
                if (it != ranges.end() && it->second == now.second.second) {
                    break;
                }
                q.pop();
            }
            results.push_back(q.empty() ? 0 : q.top().first);
        }
        return results;
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
    vector<int> nums = { 1,2,5,6,1 };
    vector<int> removeQueries = { 0,3,2,4,1 };
    Solution s;
    auto actual = s.maximumSegmentSum(nums, removeQueries);
    decltype(actual) expect = { 14,7,2,2,0 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}


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
#include <stack>

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    vector<int> smallestSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        unordered_map<int, queue<int>> indexmap;
        for (int i = 0; i < n; ++i) {
            for (int d = nums[i]; d > 0; d &= d -1) {
                indexmap[d - (d & (d - 1))].push(i);
            }
        }
        list<queue<int> *> qs;
        for (auto &r : indexmap) {
            qs.push_back(&(r.second));
        }

        vector<int> results(n);
        for (int i = 0; i < n; ++i) {
            int j = i;
            for (auto it = qs.begin(); it != qs.end(); ) {
                while (!(*it)->empty() && (*it)->front() < i) (*it)->pop();
                if ((*it)->empty()) {
                    it = qs.erase(it);
                } else {
                    j = max(j, (*it)->front());
                    ++it;
                }
            }

            results[i] = j - i + 1;
        }
        return results;

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
    vector<int> nums = { 1,0,2,1,3 };
    Solution s;
    auto actual = s.smallestSubarrays(nums);
    decltype(actual) expect = { 3,3,2,2,1 };
    EXPECT_EQ_CONTAINER(expect, actual);
}

}

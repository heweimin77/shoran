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
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> adjs(n);
        for (auto& e : edges) {
            adjs[e[0]].push_back(e[1]);
            adjs[e[1]].push_back(e[0]);
        }

        int sum = accumulate(nums.begin(), nums.end(), 0);
        int mvalue = *max_element(nums.begin(), nums.end());
        vector<int> factors = getFactors(sum, mvalue);

        function<pair<bool, int>(int, int, int)> traverse = [&](int now, int parent, int f) ->pair<bool, int> {
            int r = nums[now];
            for (auto next : adjs[now]) {
                if (next == parent) continue;
                auto [re, rr] = traverse(next, now, f);
                if (!re) return { false, -1 };
                r += rr;
            }
            if (r > f) return { false , -1 };
            if (r == f) return { true, 0 };
            return { true, r };
        };
        for (auto f : factors) {
            if (traverse(0, -1, f).first) {
                return sum / f - 1;
            }
        }
        return 0;
    }
    vector<int> getFactors(int sum, int mvalue) {
        vector<pair<int, int>> factors;
        int limit = sqrt(sum);
        for (int i = 2; i <= limit; ++i) {
            if (sum % i == 0) {
                pair<int, int> p = { i, 1 };
                sum /= i;
                while (sum % i == 0) {
                    ++p.second;
                    sum /= i;
                }
                limit = sqrt(sum);
                factors.push_back(p);
            }
        }
        if (sum > 1) {
            factors.push_back({ sum, 1 });
        }

        vector<int> results;
        function<void(int, int)> getfacts = [&](int i, long long r) {
            if (i == factors.size()) {
                results.push_back(r);
                return;
            }
            for (int j = 0; j <= factors[i].second; ++j) {
                getfacts(i + 1, r);
                r *= factors[i].first;
            }
        };
        getfacts(0, 1);
        auto it = remove_if(results.begin(), results.end(), [&](int r) {return r < mvalue; });
        results.erase(it, results.end());
        sort(results.begin(), results.end());
        results.pop_back();
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
    vector<int> nums = { 6,2,2,2,6 };
    vector<vector<int>> edges = { {0,1}, {1,2}, {1,3}, {3,4} };
    Solution s;
    auto actual = s.componentValue(nums, edges);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}


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

#include "support.h"

using namespace std;

namespace {

class Solution {
public:
    int findValidSplit(vector<int>& nums) {
        vector<int> primes = getPrimes(1000);
        int n = nums.size();
        vector<vector<int>> factors(n);
        for (int i = 0; i < n; ++i) {
            getFactors(nums[i], primes, factors[i]);
        }
        unordered_map<int, int> counts;
        for (auto& f : factors) {
            for (auto& n : f) {
                ++counts[n];
            }
        }

        int cnt = 0;
        unordered_set<int> visited;
        for (int i = 0; i < n; ++i) {
            for (auto f : factors[i]) {
                if (visited.count(f) == 0) {
                    ++cnt;
                    visited.insert(f);
                }
                if (--counts[f] == 0) --cnt;
            }
            if (cnt == 0) return i;
        }


        return -1;
    }
    vector<int> getPrimes(int maxnum)
    {
        vector<int> primes;
        vector<int> min_factor(maxnum + 1);
        for (int i = 2; i <= maxnum; ++i) {
            if (min_factor[i] == 0) {
                min_factor[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (i * p > maxnum) break;
                min_factor[i * p] = p;
                if (p == min_factor[i]) break;
            }
        }
        return primes;
    }
    void getFactors(int n, const vector<int>& primes, vector<int>& factors) {
        for (int i = 0; i < primes.size() && n > 1; ++i) {
            if (n % primes[i] == 0) {
                factors.push_back(primes[i]);
                for (n /= primes[i]; n % primes[i] == 0; n /= primes[i]);
            }
        }
        if (n > 1) factors.push_back(n);
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
    vector<int> nums = { 4,7,8,15,3,5 };
    Solution s;
    auto actual = s.findValidSplit(nums);
    decltype(actual) expect = 2;
    EXPECT_EQ(expect, actual);
}
}

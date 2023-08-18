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
    static constexpr int MOD = 1e9 + 7;
public:
    int maximumScore(vector<int>& nums, int k) {
        vector<int> primes = getPrimes(sqrt(100000) + 1);
        int n = nums.size();
        vector<int> pfactors(n);
        for (int i = 0; i < n; ++i) {
            auto  d = nums[i];
            int r = 0;
            for (auto p : primes) {
                if (d < p) break;
                if (d % p == 0) {
                    ++r;
                    d /= p;
                    while (d % p == 0) {
                        d /= p;
                    }
                }
            }
            if (d > 1) ++r;
            pfactors[i] = r;
        }
        vector<int> left(n);
        stack<pair<int, int>> s;
        s.push({ INT_MAX, -1 });
        for (int i = 0; i < n; ++i) {
            int p = pfactors[i];
            while (s.top().first < p) s.pop();
            left[i] = s.top().second;
            s.push({ p, i });
        }
        vector<int> right(n);
        stack<pair<int, int>> ss;
        s.push({ INT_MAX, n });
        for (int i = n - 1; i >= 0; --i) {
            int p = pfactors[i];
            while (s.top().first <= p) s.pop();
            right[i] = s.top().second;
            s.push({ p, i });
        }

        priority_queue<pair<int, int>> q;
        for (int i = 0; i < n; ++i) {
            q.push({ nums[i], i });
        }
        long long result = 1;
        while (k > 0) {
            auto now = q.top();
            q.pop();
            long long count = (right[now.second] - now.second) * (now.second - left[now.second]);
            if (count >= k) {
                result *= fast_power(now.first, k, MOD);
                result %= MOD;
                break;
            } else {
                result *= fast_power(now.first, count, MOD);
                result %= MOD;
                k -= count;
            }
        }

        return result;
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
    long long fast_power(long long base, long long n, long long module) {
        long long result = 1;
        int mask = 1;
        for (int mask = 1; mask <= n; mask <<= 1) {
            if (mask & n) {
                result *= base;
                result %= module;
            }
            base *= base;
            base %= module;
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
    vector<int> nums = { 8,3,9,3,8 };
    Solution s;
    auto actual = s.maximumScore(nums, 2);
    decltype(actual) expect = 81;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    vector<int> nums = { 19,12,14,6,10,18 };
    Solution s;
    auto actual = s.maximumScore(nums, 3);
    decltype(actual) expect = 4788;
    EXPECT_EQ(expect, actual);
}
}


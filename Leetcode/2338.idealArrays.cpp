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
    int idealArrays(int n, int maxValue)
    {
        vector<int> primes;
        vector<unordered_map<int, int>> counts(maxValue + 1);
        long long result = 1;
        for (int i = 2; i <= maxValue; ++i) {
            int limit = sqrt(i);
            for (auto p : primes) {
                if (p > limit) break;
                if (i % p == 0) {
                    counts[i] = counts[i / p];
                    ++counts[i][p];
                    break;
                }
            }
            if (counts[i].empty()) {
                ++counts[i][i];
                primes.push_back(i);
            }
            long long r = 1;
            for (auto &cnt : counts[i]) {
                r *= getC(n + cnt.second - 1, cnt.second);
                r %= MOD;
            }
            result += r;
        }

        return result % MOD;
    }

    long long getX(int n)
    {
        if (data.empty()) {
            data = { 1, 1, 2, 6 };
        }
        if (n >= data.size()) {
            int now = data.size() - 1;
            data.resize(n + 1);
            for (long long i = now + 1; i <= n; ++i) {
                data[i] = data[i - 1] * i % MOD;
            }
        }
        return data[n];
    }

    int getC(int n, int k)
    {
        long long x1 = getX(n);
        long long x2 = getX(k) * getX(n - k) % MOD;
        long long x2_ = invert(x2, MOD);
        return x1 * x2_ % MOD;
    }

    long long fast_power(long long base, long long n, long long module)
    {
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

    long long invert(long long a, long long p)
    {
        return fast_power(a, p - 2, p);
    }

private:
    vector<int> data;
};

class Solution1Timeout {
    static constexpr int MOD = 1e9 + 7;
public:
    int idealArrays(int n, int maxValue)
    {
        vector<int> results(maxValue + 1, 1);
        vector<int> nexts(maxValue + 1);
        for (int i = 1; i < n; ++i) {
            fill(nexts.begin(), nexts.end(), 0);
            for (int j = 1; j <= maxValue; ++j) {
                for (int k = j; k <= maxValue; k += j) {
                    nexts[k] += results[j];
                    if (nexts[k] >= MOD) nexts[k] -= MOD;
                }
            }
            results.swap(nexts);
        }
        return accumulate(results.begin(), results.end(), 0LL) % MOD;
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
    Solution s;
    auto actual = s.idealArrays(2, 5);
    decltype(actual) expect = 10;
    EXPECT_EQ(expect, actual);
}
TEST_F(TestSolution, TestMain)
{
    Solution s;
    auto actual = s.idealArrays(5, 3);
    decltype(actual) expect = 11;
    EXPECT_EQ(expect, actual);
}
}

